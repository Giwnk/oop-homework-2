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
    BANK_CAPABILITIES,
    STORE_CAPABILITIES,
    LOGIN_BACK
};

enum BuyerLoginMenuPrompt{
    CHECK_STATUS_ACCOUNT,
    UPGRADE_TO_SELLER,
    SHOW_BUYER_INFO,
    SHOW_LIST_STORES,
    SHOW_INVENTORY,
    PURCHASE_ITEM,
    SHOW_ALL_ORDERS,
    SHOW_LATEST_SPENDING,
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
    Database::isBuyer = true;
    cout << "\nBuyer Registered Successfully!\n";
    return true;
}

bool handleRegisterBankCustomer() {
    string name;
    double balance;

    cout << "=========================================================\n";
    cout << "                     REGISTER BANK CUSTOMER\n";
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
    Database::isBankLinked = true;

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

    Store* newStore = new Store(storeName);
    Seller* newSeller = new Seller(phoneNum, name, storeName, email, address, Database::loggedBankCustomer, newStore);
    newStore->setAssociatedSeller(newSeller);
    Database::loggedSeller = newSeller;
    Database::addSeller(Database::loggedSeller);
    Database::isSeller = true;
    cout << "\nSeller Registered Successfully!\n";
    return true;
}

void checkAccountStatus(){
    cout << "\n[INFO] Check Account Status selected." << endl;

    cout << "\n[User Role Status]" << endl;
    if (Database::isBuyer && Database::isSeller) {
        cout << "Your Role is Buyer and Seller." << endl;
    } else if (Database::isBuyer) {
        cout << "Your Role is Buyer." << endl;
    } else if (Database::isSeller) {
        cout << "Your Role is Seller." << endl;
    } else {
        cout << "You do not have Buyer or Seller account." << endl;
    }
    if (Database::isBuyer && Database::loggedBuyer && Database::loggedBankCustomer) {
        cout << "\n[Buyer Account Details]" << endl;
        cout << "Name : " << Database::loggedBuyer->getBuyerName() << endl;
        cout << "ID   : " << Database::loggedBuyer->getBuyerID() << endl;
        cout << "Linked Bank Account ID: " << Database::loggedBankCustomer->getId() << endl;
    }
    if (Database::isSeller && Database::loggedSeller){
        cout << "\n[Seller Account Details]" << endl;
        cout << "Store Name : " << Database::loggedSeller->getStoreName() << endl;
        cout << "Seller ID  : " << Database::loggedSeller->getSellerId() << endl;
    
    if (Database::isBankLinked && Database::loggedBankCustomer) {
        cout << "\n[Banking Account Status]" << endl;
        cout << "You have a linked banking account." << endl;
        Database::loggedBankCustomer->showInfo();
    } else {
        cout << "\nYou do not have a linked banking account." << endl;
    }
}
}

void upgradeToSeller(){
    string name, email, address, phoneNum, storeName;
    cout << "\n[INFO] Upgrade Account to Seller selected." << endl;
    if (!Database::isBankLinked) {
        cout << "Upgrade denied: You do not have a linked Bank Account!\n";
    } else if (Database::isSeller) {
        cout << " You are already a Seller!\n";
    } else {
        cout << "Input Your Name : ";
        getline(cin >> ws,name);
        cout << "Input Your Email : ";
        getline(cin, email);
        cout << "Input Your Address : ";
        getline(cin, address);
        cout << "Input Your Phone Number : ";
        getline(cin, phoneNum);
        cout << "Input Your Store Name : ";
        getline(cin, storeName);

        Database::newStore = new Store(storeName);
        Database::loggedSeller = new Seller(phoneNum, name, storeName, email, address, Database::loggedBankCustomer, Database::newStore);
        Database::addSeller(Database::loggedSeller);
        Database::isSeller = true;
        cout << "\nSeller Registered Successfully!\n";
    }
}

void showBuyerInfo(){
    Database::loggedBuyer->showInfoBuyer();
}

void showListStores(){
    for (auto &&store : Database::listStores)
    {
        cout << "======" << store->getStoreName() << "======" << endl; 
        store->showDetailStore();
        cout << "\n" << endl;
    }
}

void showInventory(){
    int inputStoreId;
    cout << "Input ID Store That You Want To See Their Inventory: ";
    cin >> inputStoreId;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (auto &&store : Database::listStores)
    {
        if (store->getStoreId() == inputStoreId)
        {
            cout << "======" << store->getStoreName() << "======" << endl; 
            store->showInventory();
            cout << "\n" << endl;
        } 
    }
}

void purchaseItem(){
    int inputItemId, inputQuantity;
    cout << "Input ID Item That You Want To Purchase: ";
    cin >> inputItemId;
    cout << "Input ID Item That You Want To Purchase: ";
    cin >> inputItemId;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Store* targetStore;
    Item* foundItem = Database::findItemById(inputItemId, targetStore);
    if (foundItem == nullptr)
    {
        cout << "\nItem With ID " << inputItemId << " Not Found In Any Store.\n" << endl;
        return;
    }

    Seller* targetSeller = targetStore->getAssociatedSeller();
    Database::loggedBuyer->purchaseItem(inputItemId,inputQuantity,targetStore,targetSeller,&Database::transactionHistory);
}

void showAllOrders(){
    string inputStatusFilter;
    cout << "\n=== LIST ALL ORDERS ===\n" << endl;
    cout << "Filter By Status (Paid, Completed, Cancelled) or Empty For All: ";
    getline(cin, inputStatusFilter);
    int ordersFound = 0;
    for (auto &&transaction : Database::transactionHistory) {
        // Logika: Tampilkan jika filter kosong ATAU jika statusnya cocok
        if (inputStatusFilter.empty() || transaction.getOrderStatus() == inputStatusFilter) {
            transaction.printReceipt();
            cout << "----------------------------------------\n";
            ordersFound++;
        }
    }

    if (ordersFound == 0) {
        cout << "\nTidak ada pesanan yang ditemukan.\n";
    }

    
}

// void showLatestSpending() {
//     int inputDays;
//     cout << "\n=== SHOW LATEST SPENDING ===\n" << endl;
//     cout << "Input Days : ";
//     cin >> inputDays;
//     cin.ignore(numeric_limits<streamsize>::max(), '\n');

//     listWithdrawalsLatestKDays(inputDays);

// }




/// =============================================================
/// Login Menu Handlers
/// =============================================================

void handleBuyerLoginMenu(){
    bool inBuyerLoginMenu = true;

    while (inBuyerLoginMenu) {
        cout << "\n=========================================================\n";
        cout << "                       BUYER MENU\n";
        cout << "=========================================================\n";
        cout << "1. Check Account Status\n";
        cout << "2. Upgrade to Seller\n";
        cout << "3. Show Buyer Info\n";
        cout << "4. Show List Stores\n";
        cout << "5. Show Inventory\n";
        cout << "6. Purchase Item\n";
        cout << "7. Show All Orders\n";
        cout << "8. Show Latest Spending\n";
        cout << "9. Logout\n";
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
        
        BuyerLoginMenuPrompt buyerLoginMenuPrompt = static_cast<BuyerLoginMenuPrompt>(choice - 1);

        switch (buyerLoginMenuPrompt)
        {
        case CHECK_STATUS_ACCOUNT:
            checkAccountStatus();
            break;
        
        case UPGRADE_TO_SELLER:
            upgradeToSeller();
            break;
        
        case SHOW_BUYER_INFO:
            showBuyerInfo();
            break;
        
        case SHOW_LIST_STORES:
            showListStores();
            break;

        case SHOW_INVENTORY:
            showInventory();
            break;
        
        case PURCHASE_ITEM:
            purchaseItem();
            break;
        
        case SHOW_ALL_ORDERS:
            showAllOrders();
            break;
        
        // case SHOW_LATEST_SPENDING:
        //     showLatestSpending();
        //     break;
        
        case LOGOUT:
            inBuyerLoginMenu = false; 
            break;
        
        default:
            break;
        }
    }

};



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
        handleBuyerLoginMenu();
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
        cout << "                       LOGIN MENU\n";
        cout << "=========================================================\n";
        cout << "1. Login As Buyer\n";
        cout << "2. Login As Seller\n";
        cout << "3. Bank Capabilities\n";
        cout << "4. Store Capabilities\n";
        cout << "5. Back To Main Menu\n";
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