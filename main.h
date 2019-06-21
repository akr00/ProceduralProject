
/** @file main.h
 * @brief the header file for main.cpp
 *
 * @author Aiden Ridgeway
 */


using namespace std;
struct Product { // used to store product information in a struct
    string manufacturer;
    string name;
    string itemTypeCode;
};

struct Statistics { //holds all statistics in one struct
    int MM;
    int VI;
    int AM;
    int VM;
    int tot;
};

string getPassword();

string encrypt(string);

void login();

int getChoice();

void AddEmployeeAcc();

void produce(vector<Product> &catalog, Statistics &stats);

void newProduct(vector<Product> &catalog, Statistics &stats);

void showStats(vector<Product> &catalog, Statistics &stats);

int productTypeMenu();

int statMenu();

void search(const string &);

bool compare(const std::string &a, const std::string &b) { return a < b; }

void readFiles(vector<Product> &catalog, Statistics &stats);


//end .h