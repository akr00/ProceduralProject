/**@file main.cpp
 * @brief A production line tracker
 *
 * @author Aiden Ridgeway
 * @bug none
 */

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cstring>
#include "main.h"

using namespace std;

int main() {
    vector<Product> catalog;
    Statistics stats{};

    readFiles(catalog, stats);

    int choice = 0;
    cout << "Production Line Tracker\n" << endl;
    do {
        choice = getChoice();

        switch (choice) {
            case 1 :
                //cout << "You Entered 1 \n" << endl;
                produce(catalog, stats);
                break;
            case 2:
                //cout << "You Entered 2 \n" << endl;
                AddEmployeeAcc();
                break;
            case 3:
                //cout << "You Entered 3 \n" << endl;
                newProduct(catalog, stats);
                break;
            case 4:
                //cout << "You Entered 4 \n" << endl;
                showStats(catalog, stats);
                break;
            case 5:
                //cout << "You Entered 5 \n" << endl;
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
 *
 * @param catalog
 * @param stats
 */

void newProduct(vector<Product> &catalog, Statistics &stats) {
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
    output = manufacturer + "," + name + "," + type;
    cout << "Creating the " << output << endl;
    ofstream myOFile;
    myOFile.open("catalog.csv", ios::app);
    myOFile << (output) << endl;
    readFiles(catalog, stats);
    /*
    ofstream myPOFile;
    myPOFile.open((output), ios::app);
    myPOFile << 0 << endl;
    myPOFile.close();
     */
}

/** @brief creates a new account by taking input and creating a user name and gets a password then stores them to a file.
 *
 *
 *
 */
void AddEmployeeAcc() {

    cout << "Enter your full first and last name --> " << flush;
    string firstName, lastName;
    cin >> firstName >> lastName;
    string encryptedPass;

    transform(firstName.begin(), firstName.end(), firstName.begin(), ::tolower); //sets to lowercase
    transform(lastName.begin(), lastName.end(), lastName.begin(), ::tolower);
    string username = firstName.substr(0, 1) +
                      lastName;  // sets username to the first letter of first name + last name... for Aiden Ridgeway, it would be aridgeway

    cout << "Your username is: " << username << endl;
    bool valid;
    string password;
    do {  // checks for a valid password
        bool cap = false;
        bool num = false;
        bool low = false;
        bool sym = true;

        password = getPassword();
        for (char i : password) {
            if (isupper(i))  // if capital
                cap = true;
            else
                low = true; // if lower
            if (isdigit(i))
                num = true;
            if (ispunct(i) || isspace(i))  // if has special character
                sym = false;
        }
        valid = (cap && low && num && sym);

        if (valid) {
            cout << "Your password is --> " << password << endl;
        } else {
            cout << "Invalid password" << endl;
        }
    } while (!valid);

    encryptedPass = encrypt(password); // encrypts password
    //cout << encryptedPass;
    ofstream outFile;
    outFile.open("users", ios::app);
    outFile << username << "," << encryptedPass << endl; // outputs to a file
    outFile.close();
}

/**
 * @brief creates new product--
 *
 * asks which product from the catalog is being made, then how many.
 * crates each product with an individual production number and serial number.
 * outputs each product to the productionLog
 * also keeps track of how many of each were made
 *
 * @param catalog
 * @param stats
 */
void produce(vector<Product> &catalog, Statistics &stats) {
    string line;
    int i = 0; // acts as a counter to have a way to enter a number for choice of product
    int productionNumber;
    productionNumber = stats.tot;
    int itemCount = 0;

    for (const auto &s: catalog) {  // prints each product with a corresponding number, stating at 1
        i++;
        cout << i << ". " << s.manufacturer << " " << s.name << " " << s.itemTypeCode << endl;
    }

    cout << "\nWhich Product is Being Produced...\nEnter the Number --> " << flush;
    int productChoice = 0;
    cin >> productChoice;
    string type, name, man;
    string product;
    type = catalog[productChoice - 1].itemTypeCode;  // gets each part of the product to be used individually
    name = catalog[productChoice - 1].name;
    man = catalog[productChoice - 1].manufacturer;

    //Finds the product type count for the corresponding type
    if (type == "MM") {
        itemCount = stats.MM;
    } else if (type == "VI") {
        itemCount = stats.VI;
    } else if (type == "AM") {
        itemCount = stats.AM;
    } else if (type == "VM") {
        itemCount = stats.VM;
    }

    if (productChoice <= (i)) {  // if choice is valid

        product = man + " " + name + " " + type;

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
                    << setfill(' ') << product.substr(0, (product.length()))
                    << " |||| Serial # " << man.substr(0, 3)
                    << type << setw(6) << setfill('0') << itemCount
                    << endl;
        }

    } else { //will not do anything else, didnt change values
        cout << "Invalid Selection..." << endl;
    }
    if (type == "MM") {
        stats.MM = itemCount;
    } else if (type == "VI") {
        stats.VI = itemCount;
    } else if (type == "AM") {
        stats.AM = itemCount;
    } else if (type == "VM") {
        stats.VM = itemCount;
    }
    stats.tot = productionNumber;
    ofstream myCOFile;          //vvv   updates the number of total products that have been made
    myCOFile.open("countProductionRecord");
    myCOFile << stats.MM << "," << stats.VI << "," << stats.AM << "," << stats.VM << "," << stats.tot;
    myCOFile.close();
}

/** @brief a way to show the production stastics
 *
 * @param catalog
 * @param stats
 */
void showStats(vector<Product> &catalog, Statistics &stats) {
    cout << "Total Products Created: " << stats.tot << endl;
    cout << "Total Audio Products Created: " << stats.MM << endl;
    cout << "Total Video Products Created: " << stats.VI << endl;
    cout << "Total Audio Mobile Products Created: " << stats.AM << endl;
    cout << "Total Video Mobile Products Created: " << stats.VM << endl;
    cout << endl;
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
        vector<string> temp;
        temp.reserve(catalog.size()); for (const auto &i : catalog) {
            temp.push_back(i.name);
        }
        sort(temp.begin(), temp.end(), compare);

        for (const auto &i : catalog) {
            cout << i.name << endl;
        }

    } else if (chosen == 3) {
        vector<string> tempMan;
        tempMan.reserve(catalog.size()); for (const auto &i : catalog) {
            tempMan.push_back(i.name);
        }
        sort(tempMan.begin(), tempMan.end(), compare);

        for (const auto &i : catalog) {
            cout << i.manufacturer << endl;
        }
    } else if (chosen == 4) {
        string serial;
        cout << "What is the Serial Number -->  " <<
             flush;
        cin >>
            serial;
        search(serial);

    } else {
        cout << "Unable to open file";
    }
}

/**
 * @brief Shows a menu and gathers user input to select an option.
 *
 * @return a menu choice
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
/**
 * @brief Shows a menu and gathers user input to select an option.
 *
 * @return a menu choice
 */
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
/**@brief takes a string input, then searches a file for the input
 *
 * @param input
 */
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
/**@brief gets input for a password
 *
 * @return string (password)
 */
string getPassword() {
    cout
            << "\nThe password must contain at least one digit, at least one lowercase letter, and at least one uppercase letter.\n"
            <<
            "The password cannot contain a space or any other symbols\n    " << "Create your password -->" << flush;

    string pass;
    cin >> pass;

    return pass;
}
/**@brief takes in password, then encrypts it and returns it
 *
 * @param str
 * @return encrypted password
 */
string encrypt(string str) {
    if (str.length() == 0) {
        return str;
    } else {
        return char((int) str[0] + 17) + encrypt(str.substr(1, str.length() - 1));
    }
}
/**@brief askes for input of username and password, checks if correct
 *
 */
void login() {

    ifstream myFile("users");
    vector<string> users;
    vector<string> keys;
    string user, pass;

    while (myFile.good())  // takes a line form the file then is used to output
    {
        getline(myFile, user, ',');
        getline(myFile, pass);

        users.push_back(user);
        keys.push_back(pass);
        // cout << user << " " << pass << endl;
    }

    string username, password;
    cout << "Enter username -->" << flush;
    cin >> username;
    cout << "Enter password -->" << flush;
    cin >> password;
    password = encrypt(password);
    bool correctName = false;
    bool correctPass = false;
    int count = 0;
    for (const auto &userInput : users) {
        if (userInput == username) {
            correctName = true;
            break;
        }
        count++;
    }
    //cout << count << endl;
    if (!correctName) {
        cout << "Not Valid Username" << endl;
    }
    if (keys[count] == password) {
        correctPass = true;
    } else
        cout << "Incorrect Password" << endl;

    if (correctName && correctPass) {
        cout << "Login Successful" << endl;
    }

}
/**@brief reads all necessary info from each line of the storaage files
 *
 * @param catalog
 * @param stats
 */
void readFiles(vector<Product> &catalog, Statistics &stats) {
    Product tempProduct;
    Statistics tempStats{};

    ifstream myFile("catalog.csv");
    string line, no, name, man, type;
    if (myFile.is_open()) {
        while (myFile.good())  // takes a line form the file then is used to output
        {
            getline(myFile, man, ',');
            getline(myFile, name, ',');
            getline(myFile, type);

            tempProduct.name = name;
            tempProduct.manufacturer = man;
            tempProduct.itemTypeCode = type;
            catalog.push_back(tempProduct);

        }
        myFile.close();
        catalog.pop_back();
    }

    ifstream myRecFile("countProductionRecord");
    string vm, am, vi, mm, tot;
    if (myRecFile.is_open()) {
        while (myRecFile.good()) {
            getline(myRecFile, mm, ',');
            getline(myRecFile, vi, ',');
            getline(myRecFile, am, ',');
            getline(myRecFile, vm, ',');
            getline(myRecFile, tot);

            tempStats.AM = stoi(am);
            tempStats.VM = stoi(vm);
            tempStats.MM = stoi(mm);
            tempStats.VI = stoi(vi);
            tempStats.tot = stoi(tot);
            stats = (tempStats);

        }
        myRecFile.close();
    }
}
