#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>

#include "Database.cpp"
#include "Handlers/handlers.cpp"
using namespace std;

enum PrimaryPrompt {
    LOGIN,
    REGISTER,
    EXIT_PROGRAM,
    MAIN_PROMPT
};

enum RegisterPrompt {
    REGISTER_AS_BUYER,
    REGISTER_AS_SELLER,
    REGISTER_AS_BANK_CUSTOMER,
    BACK,
    MAIN_REGISTER_PROMPT
};

enum LoginPrompt{
    LOGIN_AS_BUYER,
    LOGIN_AS_SELLER,
    LOGOUT
};

/// =============================================================
/// Utility Functions
/// =============================================================

/// =============================================================
/// Register Handlers
/// =============================================================

bool handleRegisterAsBuyer() {
    
    string name, email, address, phoneNum;

    cout << "=========================================================\n";
    cout << "                       REGISTER AS BUYER\n";
    cout << "=========================================================\n";

    if (Database::loggedBankCustomer == nullptr) {
        cout << "\nYou don't have a Bank Customer account.\n";
        cout << "   Please register as Bank Customer first.\n";
        return false;
    }

    cout << "Input Your Name           : ";
    getline(cin >> ws,name);
    cout << "Input Your Email          : ";
    getline(cin, email);
    cout << "Input Your Address        : ";
    getline(cin, address);
    cout << "Input Your Phone Number   : ";
    getline(cin, phoneNum);

    Database::loggedBuyer = new Buyer(phoneNum, name, email, address, Database::loggedBankCustomer);
    Database::addBuyer(Database::loggedBuyer);
    
    cout << "\nBuyer Registered Successfully!\n";
    return true;
}

bool handleRegisterBankCustomer() {
    string name;
    double balance;

    cout << "=========================================================\n";
    cout << "                     REGISTER AS BANK CUSTOMER\n";
    cout << "=========================================================\n";

    cout << "Input Your Name    : ";
    getline(cin >> ws,name);
    cout << "Input Your Balance : ";

    while (!(cin >> balance)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Database::loggedBankCustomer = new BankCustomer(name, balance);
    Database::mainBank.addBankCustomer(*Database::loggedBankCustomer);

    cout << "\nBank Customer Registered Successfully!\n";
    return true;
}

bool handleRegisterAsSeller(){
    string name, email, address, phoneNum, storeName;

    cout << "=========================================================\n";
    cout << "                       REGISTER AS SELLER\n";
    cout << "=========================================================\n";

    if (Database::loggedBankCustomer == nullptr) {
        cout << "\nYou don't have a Bank Customer account.\n";
        cout << "   Please register as Bank Customer first.\n";
        return false;
    }

    cout << "Input Your Name           : ";
    getline(cin >> ws,name);
    cout << "Input Your Email          : ";
    getline(cin, email);
    cout << "Input Your Address        : ";
    getline(cin, address);
    cout << "Input Your Phone Number   : ";
    getline(cin, phoneNum);
    cout << "Input Your Store Name   : ";
    getline(cin, storeName);

    Database::newStore = new Store(storeName);
    Database::loggedSeller = new Seller(phoneNum, name, storeName, email, address, Database::loggedBankCustomer, Database::newStore);
    Database::addSeller(Database::loggedSeller);
    cout << "\nSeller Registered Successfully!\n";
    return true;
}


/// =============================================================
/// Login Handlers
/// =============================================================

void handleBuyerLogin() {
    cout << "\n=========================================================\n";
    cout << "                        BUYER LOGIN\n";
    cout << "=========================================================\n";
    
    string name;
    cout << "Enter your name to login: ";
    getline(cin, name);

    Buyer* foundBuyer = Database::findBuyerByName(name);

    if (foundBuyer != nullptr) {
        Database::loggedBuyer = foundBuyer;
        cout << "\nWelcome back, " << Database::loggedBuyer->getBuyerName() << "!";
        cout << "\nLogin successful!\n";
        // Di sini Anda bisa arahkan ke menu khusus buyer
        // contoh: showBuyerMenu();
    } else {
        cout << "\nLogin failed. Buyer with name '" << name << "' not found.\n";
    }
}

void handleSellerLogin() {
    cout << "\n=========================================================\n";
    cout << "                        SELLER LOGIN\n";
    cout << "=========================================================\n";

    string name;
    cout << "Enter your name to login: ";
    getline(cin, name);

    Seller* foundSeller = Database::findSellerByName(name);

    if (foundSeller != nullptr) {
        Database::loggedSeller = foundSeller;
        Database::loggedBankCustomer = foundSeller->getBuyerAccount();
        cout << "\nWelcome back, " << Database::loggedSeller->getBuyerName() << "!";
        cout << "\nLogin successful! You are logged in as a seller.\n";
        // Di sini Anda bisa arahkan ke menu khusus seller
        // contoh: showSellerMenu();
    } else {
        cout << "\nLogin failed. Seller with name '" << name << "' not found.\n";
    }
}





/// =============================================================
/// Menus
/// =============================================================
void handleRegisterMenu() {
    bool inRegisterMenu = true;

    while (inRegisterMenu) {
        cout << "\n=========================================================\n";
        cout << "                       REGISTER MENU\n";
        cout << "=========================================================\n";
        cout << "1. Register as Buyer\n";
        cout << "2. Register as Seller\n";
        cout << "3. Register as Bank Customer\n";
        cout << "4. Back\n";
        cout << "=========================================================\n";
        cout << "Select option (1-4): ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input! Please enter a number (1-4).\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        RegisterPrompt registerPrompt = static_cast<RegisterPrompt>(choice - 1);

        switch (registerPrompt) {
            case REGISTER_AS_BUYER:
                handleRegisterAsBuyer();
                break;

            case REGISTER_AS_SELLER:
                handleRegisterAsSeller();
                break;

            case REGISTER_AS_BANK_CUSTOMER:
                handleRegisterBankCustomer();
                break;

            case BACK:
                inRegisterMenu = false;
                break;

            default:
                cout << "\nPlease select a valid option (1-4)!\n";
                break;
        }
    }
}

void handleLoginMenu(){
    bool inLoginMenu = true;

    while (inLoginMenu) {
        cout << "\n=========================================================\n";
        cout << "                       REGISTER MENU\n";
        cout << "=========================================================\n";
        cout << "1. Login As Buyer\n";
        cout << "2. Login As Seller\n";
        cout << "3. Logout\n";
        cout << "=========================================================\n";
        cout << "Select option (1-4): ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input! Please enter a number (1-4).\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        LoginPrompt loginPrompt = static_cast<LoginPrompt>(choice - 1);

        switch (loginPrompt)
        {
        case LOGIN_AS_BUYER:
            handleBuyerLogin();
            break;
        
        case LOGIN_AS_SELLER:
            handleSellerLogin();
            break;
        
        case LOGOUT:
            inLoginMenu = false; 
            break;
        
        default:
            break;
        }
    }
}

/// =============================================================
/// Main Program
/// =============================================================
int main() {
    PrimaryPrompt primaryPrompt = MAIN_PROMPT;
    int choice;

    while (primaryPrompt != EXIT_PROGRAM) {
        cout << "\n=========================================================\n";
        cout << "               WELCOME TO MINI BANK SYSTEM\n";
        cout << "=========================================================\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cout << "=========================================================\n";
        cout << "Select option (1-3): ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input! Please enter 1, 2, or 3.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        primaryPrompt = static_cast<PrimaryPrompt>(choice - 1);
        switch (primaryPrompt) {
            case LOGIN:
                handleLoginMenu();
                primaryPrompt = MAIN_PROMPT;
                break;

            case REGISTER:
                handleRegisterMenu();
                primaryPrompt = MAIN_PROMPT; 
                break;

            case EXIT_PROGRAM:
                cout << "\nThank you for using the system!\n";
                cout << "Goodbye!\n";
                return 0;

            default:
                cout << "\nPlease select a valid option!\n";
                break;
        }
    }

    return 0;
}