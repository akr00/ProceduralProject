/**@file main.cpp
 * @brief The whole program(for now)
 *
 *
 *
 * @author Aiden Ridgeway
 * @bug breaks / loops when a space is entered in the 'cin' within newProduct
 */

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cstring>

using namespace std;

string getPassword();

string encrypt(string);

void login();

int getChoice();

void AddEmployeeAcc();

void produce();

void newProduct();

void showStats();

int productTypeMenu();

int statMenu();

void search(const string &);

bool compare(const std::string &a, const std::string &b) { return a < b; }

int main() {
    int choice = 0;
    cout << "Production Line Tracker\n" << endl;
    do {
        choice = getChoice();


        switch (choice) {
            case 1 :
                cout << "You Entered 1 \n" << endl;
                produce();
                break;
            case 2:
                cout << "You Entered 2 \n" << endl;
                AddEmployeeAcc();
                break;
            case 3:
                cout << "You Entered 3 \n" << endl;
                newProduct();
                break;
            case 4:
                cout << "You Entered 4 \n" << endl;
                showStats();
                break;
            case 5:
                cout << "You Entered 5 \n" << endl;
                login();
                break;
            case 6:
                cout << "Exiting...\n" << "Thank you for using" << endl;
                break;
            default:
                cout << "Enter a Valid Choice..." << endl;
                cin.clear();
                cin.ignore();
        }
    } while (choice != 6);


    return 0;
}

/**
 * @brief Shows a menu and gathers user input to select an option.
 * @return the choice
 */
int getChoice() {
    int pick = 0;

    cout << "\n1. Produce Products" << endl;
    cout << "2. Add Employee Account" << endl;
    cout << "3. Add New Product" << endl;
    cout << "4. Display Production Statistics" << endl;
    cout << "5. Login" << endl;
    cout << "6. Exit\n" << endl;

    cout << "Enter your choice --> " << flush;
    cin >> pick;

    return pick;
}

/**
 * @brief Made for creating new products, acquires all information and creates it in a text file
 *
 * catalog holds all of the created products
 * a file to count each item's production numbers is also created here
 */

void newProduct() {
    string manufacturer;
    string name;
    string type;
    string output;
    int typeChoice;
    cout << "Creating new Product.." << endl;
    cout << "Enter the Manufacturer --> " << flush;
    cin.ignore();
    getline(cin, manufacturer);
    cout << "\n Enter the Product Name --> " << flush;
    getline(cin, name);
    cout << "Select the Product Type Code:" << flush;
    do {
        typeChoice = productTypeMenu();

        if (typeChoice == 1) {
            type = "MM";
        } else if (typeChoice == 2) {
            type = "VI";
        } else if (typeChoice == 3) {
            type = "AM";
        } else if (typeChoice == 4) {
            type = "VM";
        }

    } while (typeChoice > 4 || typeChoice < 0);
    output = manufacturer + ", " + name + ", " + type + ", ";
    cout << "Creating the " << output << endl;
    ofstream myOFile;
    myOFile.open("catalog.csv", ios::app);
    myOFile << (output) << endl;
    /*
    ofstream myPOFile;
    myPOFile.open((output), ios::app);
    myPOFile << 0 << endl;
    myPOFile.close();
     */
}

void AddEmployeeAcc() {

    cout << "Enter your full first and last name --> " << flush;
    string firstName, lastName;
    cin >> firstName >> lastName;
    string encryptedPass;

    transform(firstName.begin(), firstName.end(), firstName.begin(), ::tolower);
    transform(lastName.begin(), lastName.end(), lastName.begin(), ::tolower);
    string username = firstName.substr(0, 1) + lastName;

    cout << "Your username is: " << username << endl;
    bool valid;
    string password;
    do {
        bool cap = false;
        bool num = false;
        bool low = false;
        bool sym = true;

        password = getPassword();
        for (int i = 0; i < password.length(); i++) {
            if (isupper(password[i]))
                cap = true;
            else
                low = true;
            if (isdigit(password[i]))
                num = true;
            if(ispunct(password[i]) || isspace(password[i]))
                sym = false;
        }
        valid = (cap && low && num && sym);

        if (valid) {
            cout << "Your password is --> " << password << endl;
        } else {
            cout << "Invalid password" << endl;
        }
    } while (!valid);

    encryptedPass = encrypt(password);
    cout << encryptedPass;
    ofstream outFile;
    outFile.open("users", ios::app);
    outFile << username << "," << encryptedPass << "," << endl;


}

/**
 * @brief creates new product--
 *
 * asks which product from the catalog is being made, then how many.
 * crates each product with an individual production number and serial number.
 * outputs each product to the productionLog
 * also keeps track of how many of each were made
 *
 */
void produce() {
    string line;
    int i = 0;
    int productionNumber;
    int itemCount = 0;

    //Opens files

    ifstream myCFile;
    myCFile.open("countProductionRecord", ios::app);
    myCFile >> productionNumber;
    myCFile.close();
    ifstream myFile("catalog.csv");

    //shows a menu for the available products

    if (myFile.is_open()) {
        while (getline(myFile, line))  // takes a line form the file then is used to output
        {
            if (i == 0) {
                i++;
                continue;
            } else {

                cout << i << ". " << line << endl;
                i++;
            }
        }
        myFile.close();
    } else cout << "Unable to open file";
    cout << "\nWhich Product is Being Produced...\nEnter the Number --> " << flush;
    int productChoice = 0;
    cin >> productChoice;
    string type, name, man;
    string product;
    ifstream mySFile("catalog.csv");

    //Finds the actual product with corresponding choice

    for (int h = 1; h <= (productChoice + 1); h++) {

        getline(mySFile, man, ',');
        getline(mySFile, name, ',');
        getline(mySFile, type, ',');

    }
    if (productChoice <= (i - 1)) {
        ifstream myPIFile;
        myPIFile.open((type + "counter"), ios::app);
        myPIFile >> itemCount;
        myPIFile.close();
        product = man + name + type;

        cout << "You Selected : " << product << endl;
        cout << "\nHow Many Are Being Produced -->" << flush;
        int quantity = 0;
        cin >> quantity;
        ofstream myPFile;
        myPFile.open("productionLog", ios::app);

        //writes to production log with my design

        for (int j = 0; j < quantity; j++) {
            ++productionNumber;
            ++itemCount;
            myPFile << " |||| Production # " << setw(6) << setfill('0') << productionNumber << " |||| " << setw(25)
                    << setfill(' ') << product.substr(1, (product.length()))
                    << " |||| Serial # " << man.substr(1, 3)
                    << (type.substr(1, 2)) << setw(6) << setfill('0') << itemCount
                    << endl;
        }

    } else {
        cout << "Invalid Selection..." << endl;
    }
    ofstream myCOFile;          //vvv   updates the number of total products that have been made
    myCOFile.open("countProductionRecord");
    myCOFile << productionNumber;
    myCOFile.close();
    ofstream myPFile;            //vvv   updates the number of each product that have been made
    myPFile.open(type + "counter");
    myPFile << itemCount;
    myPFile.close();


}

void showStats() {
    string line;
    int chosen = statMenu();

    if (chosen == 1) {
        ifstream myFile("productionLog");
        if (myFile.is_open()) {

            while (getline(myFile, line))  // takes a line form the file then is used to output
            {
                cout << line << endl;

            }
            myFile.close();
        } else cout << "Unable to open file";
    } else if (chosen == 2) {

        ifstream myFile("catalog.csv");
        if (myFile.is_open()) {
            vector<string> temp;
            string man, name, type, no;


            while (getline(myFile, no))  // takes a line form the file then is used to output
            {

                getline(myFile, man, ',');
                getline(myFile, name, ',');
                getline(myFile, type, ',');

                temp.push_back(name);


            }
            temp.pop_back();
            sort(temp.begin(), temp.end(), compare);
            myFile.close();

            for (const string &i : temp) {
                cout << i << endl;
            }


        } else cout << "Unable to open file";
    } else if (chosen == 3) {

        ifstream myFile("catalog.csv");
        if (myFile.is_open()) {
            vector<string> temp;
            string man, name, type, no;


            while (getline(myFile, no))  // takes a line form the file then is used to output
            {

                getline(myFile, man, ',');
                getline(myFile, name, ',');
                getline(myFile, type, ',');

                temp.push_back(man);


            }
            temp.pop_back();
            sort(temp.begin(), temp.end(), compare);
            myFile.close();

            for (const string &i : temp) {
                cout << i << endl;
            }


        } else cout << "Unable to open file";
    } else if (chosen == 4) {
        string serial;
        cout << "What is the Serial Number -->  " << flush;
        cin >> serial;
        search(serial);

    } else {
        showStats();
    }
}

/**
 * @brief Shows a menu and gathers user input to select an option.
 *
 * @return
 */
int productTypeMenu() {
    int pick = 0;
    cout << "Product Type Menu \n" << endl;
    cout << "1. Audio('MM') " << endl;
    cout << "2. Visual('VI'')" << endl;
    cout << "3. AudioMobile('AM')" << endl;
    cout << "4. VisualMobile('VM'')" << endl;
    cout << "Enter your choice(1,2,3,4) --> " << flush;
    cin >> pick;
    return pick;
}

int statMenu() {
    int choice;
    cout << "1. Show Production Log" << endl;
    cout << "2. Show Product Names" << endl;
    cout << "3. Show Manufactures" << endl;
    cout << "4. Search by Serial Number" << endl;
    cout << "\n   Enter Menu Choice --> " << flush;
    cin >> choice;


    return choice;
}

void search(const string &input) {
    ifstream fileInput("productionLog");
    string line;
    for (unsigned int curLine = 0; getline(fileInput, line); curLine++) {
        if (line.find(input) != string::npos) {
            cout << "Found -->  " << line.substr(5, 20) << endl;
            break;
        }
    }
}

string getPassword() {
    cout
            << "\nThe password must contain at least one digit, at least one lowercase letter, and at least one uppercase letter.\n"
            <<
            "The password cannot contain a space or any other symbols\n    " << "Create your password -->" << flush;

    string pass;
    cin >> pass;


    return pass;
}


string encrypt(string str) {
    if (str.length() == 0) {
        return str;
    } else {
        return char((int) str[0] + 17) + encrypt(str.substr(1, str.length() - 1));
    }
}

void login(){

    ifstream myFile("users");
    vector<string> users;
    vector<string> keys;
    string user, pass;

    while (myFile.good())  // takes a line form the file then is used to output
    {

        getline(myFile, user, ',');
        getline(myFile, pass, ',');


        users.push_back(user);
        keys.push_back(pass);
        cout << user << " " << pass << endl;

    }

    string username, password;
    cout << "Enter username -->" << flush;
    cin >> username;
    cout << endl;
    cout << "Enter password -->" << flush;
    cin >> password;
    password = encrypt(password);
    bool correctName = false;
    bool correctPass = false;
    int count = 0;
    for (int i = 0 ; i < users.size(); i++) {
        if(users[i] == username){
            correctName = true;
            break;
        }
        count++;
    }
    cout << count << endl;
    if(!correctName) {
        cout << "Not Valid Username" << endl;
    }
    if(keys[count] == password){
        correctPass = true;
    }
    else
        cout << "Incorrect Password" << endl;

    if(correctName && correctPass){
        cout << "Login Successful" << endl;
    }

}