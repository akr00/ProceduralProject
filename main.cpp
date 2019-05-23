// Created by Aiden Ridgeway
//      on 5/17/19
//     Procedual Project
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int getChoice();

void AddEmployeeAcc();

void produce();

void newProduct();

void showStats();

int productTypeMenu();

int main() {
    int choice = 0;

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
                cout << "Exiting...\n" << "Thank you for using" << endl;
                break;
            default:
                cout << "Enter a Valid Choice..." << endl;

        }
    } while (choice != 5);


    return 0;
}

int getChoice() {
    int pick = 0;
    cout << "\n\nProduction Line Tracker\n" << endl;
    cout << "1. Produce Products" << endl;
    cout << "2. Add Employee Account" << endl;
    cout << "3. Add New Product" << endl;
    cout << "4. Display Production Statistics" << endl;
    cout << "5. Exit\n" << endl;
    cout << "Enter your choice --> " << flush;
    cin >> pick;

    return pick;
}

/**
 * Made for creating new products, acquires all information and creates it in a text file
 */

void newProduct() {
    string manufacturer;
    string name;
    string type;
    string output;
    int typeChoice;
    cout << "Creating new Product.." << endl;
    cout << "Enter the Manufacturer --> " << flush;
    cin >> manufacturer;
    cout << "\n Enter the Product Name --> " << flush;
    cin >> name;
    cout << "Select the Product Type Code:";
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
    output = manufacturer + " " + name + " " + type;
    cout << "Creating the " << output << endl;
    ofstream myOFile;
    myOFile.open("catalog", ios::app);
    myOFile << output << endl;
    ofstream myPOFile;
    myPOFile.open((output + "(counter)"), ios::app);
    myPOFile << 0 << endl;
    myPOFile.close();
}

void AddEmployeeAcc() {

}

void produce() {
    string line;
    int i = 1;
    int productionNumber;
    int itemCount = 0;
    ifstream myCFile;
    myCFile.open("countProductionRecord", ios::app);
    myCFile >> productionNumber;
    myCFile.close();
    ifstream myFile("catalog");
    if (myFile.is_open()) {
        while (getline(myFile, line))  // takes a line form the file then is used to output
        {

            cout << i << ". " << line << endl;
            i++;
        }
        // myFile.close();
    } else cout << "Unable to open file";
    cout << "\nWhich Product is Being Produced...\nEnter the Number --> " << flush;
    int productChoice = 0;
    cin >> productChoice;

    string product;
    ifstream mySFile("catalog");
    for (int i = 0; i <= (productChoice - 1); i++) {
        getline(mySFile, product);
    }
    if (productChoice <= (i - 1)) {

        ifstream myPIFile;
        myPIFile.open(product, ios::app);
        myPIFile >> itemCount;
        myPIFile.close();

        cout << "You Selected : " << product << endl;
        cout << "\nHow Many Are Being Produced -->" << flush;
        int quantity = 0;
        cin >> quantity;
        ofstream myPFile;
        myPFile.open("productionLog", ios::app);
        for (int j = 0; j < quantity; j++) {
            ++productionNumber;
            ++itemCount;
            myPFile << " |||| Production # " << setw(6) << setfill('0') << productionNumber << " |||| " << setw(25)
                    << setfill(' ') << product
                    << " |||| Serial # " << product.substr(0,3) << product.substr((product.length()-2), product.length())<< setw(6) << setfill('0') << itemCount << endl;
        }

    } else {
        cout << "Invalid Selection..." << endl;
    }
    ofstream myCOFile;
    myCOFile.open("countProductionRecord");
    myCOFile << productionNumber;
    myCOFile.close();
    ofstream myPFile;
    myPFile.open((product + "(counter)"));
    myPFile << itemCount;
    myPFile.close();

}

void showStats() {

}

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