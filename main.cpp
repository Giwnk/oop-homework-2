#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>

#include "Database.h"
#include "Handlers/handlers.h"
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
    SHOW_INVENTORY_FOR_BUYER,
    PURCHASE_ITEM,
    SHOW_ALL_ORDERS,
    SHOW_LATEST_SPENDING,
    LOGOUT_BUYER
};

enum SellerLoginMenuPrompt{
    SHOW_SELLER_INFO,
    ADD_ITEM,
    UPDATE_ITEM,
    SHOW_INVENTORY_FOR_SELLER,
    SHOW_ORDERS,
    UPDATE_ORDER_STATUS,
    SHOW_TOP_ITEMS,
    SHOW_LOYAL_CUSTOMERS,
    CHECK_BALANCE,
    LOGOUT_SELLER
};

enum BankCapabilitiesPrompt{
    LIST_ALL_BANK_CUSTOMERS,
    SEARCH_CUSTOMERS_BY_ID,
    SHOW_LATEST_WEEK_TRANSACTION,
    FILTER_TRANSACTION_BY_TYPE,
    SHOW_DORMANT_CUSTOMERS,
    SHOW_TOP_ACTIVE_USERS,
    LOGOUT_BANK

};

enum StoreCapabilitiesPrompt{
    LIST_ALL_TRANSACTION_OF_THE_LATEST_K_DAYS,
    LIST_ALL_PENDING_TRANSACTIONS,
    LIST_MOST_FREQUENT_M_ITEMS,
    LIST_MOST_ACTIVE_BUYERS_PER_DAY,
    LIST_MOST_ACTIVE_SELLERS_PER_DAY,
    LOGOUT_STORE
};


/// =============================================================
/// Register Handlers
/// =============================================================

void handleRegisterAsBuyer() {
    
    string name, email, address, phoneNum;

    cout << "=========================================================\n";
    cout << "                       REGISTER AS BUYER\n";
    cout << "=========================================================\n";

    if (Database::loggedBankCustomer == nullptr) {
        cout << "\nYou don't have a Bank Customer account.\n";
        cout << "   Please register as Bank Customer first.\n";
        pressEnterToContinue();
        return;
    }

    cout << "Input Your Name           : ";
    getline(cin >> ws,name);

    cout << "Input Your Email          : ";
    getline(cin, email);
    cout << "Input Your Address        : ";
    getline(cin, address);
    cout << "Input Your Phone Number   : ";
    getline(cin, phoneNum);

    Database::loggedBuyer = new Buyer(name, email, address, phoneNum, Database::loggedBankCustomer);
    Database::addBuyer(Database::loggedBuyer);
    Database::isBuyer = true;
    cout << "\nBuyer Registered Successfully!\n";
}

void handleRegisterBankCustomer() {
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
}

void handleRegisterAsSeller(){
    string name, email, address, phoneNum, storeName;

    cout << "=========================================================\n";
    cout << "                       REGISTER AS SELLER\n";
    cout << "=========================================================\n";

    if (Database::loggedBankCustomer == nullptr) {
        cout << "\nYou don't have a Bank Customer account.\n";
        cout << "   Please register as Bank Customer first.\n";
        pressEnterToContinue();
        return;
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
    Seller* newSeller = new Seller(name, email, address, phoneNum, Database::loggedBankCustomer,storeName, newStore);
    newStore->setAssociatedSeller(newSeller);
    Database::loggedSeller = newSeller;
    Database::addSeller(Database::loggedSeller);
    Database::isSeller = true;
    cout << "\nSeller Registered Successfully!\n";
}

/// =============================================================
/// Login Menu Handlers
/// =============================================================

void handleBuyerLoginMenu(){
    clearScreen();
    bool inBuyerLoginMenu = true;

    while (inBuyerLoginMenu) {
        clearScreen();
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
        cout << "Select option (1-9): ";

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
            clearScreen();
            checkAccountStatus();
            pressEnterToContinue();
            break;
        
        case UPGRADE_TO_SELLER:
            clearScreen();
            upgradeToSeller();
            pressEnterToContinue();
            break;
        
        case SHOW_BUYER_INFO:
            clearScreen();
            showBuyerInfo();
            pressEnterToContinue();
            break;
        
        case SHOW_LIST_STORES:
            clearScreen();
            showListStores();
            pressEnterToContinue();
            break;

        case SHOW_INVENTORY_FOR_BUYER:
            clearScreen();
            showInventory();
            pressEnterToContinue();
            break;
        
        case PURCHASE_ITEM:
            clearScreen();
            purchaseItem();
            pressEnterToContinue();
            break;
        
        case SHOW_ALL_ORDERS:
            clearScreen();
            showAllOrders();
            pressEnterToContinue();
            break;
        
        case SHOW_LATEST_SPENDING:
            clearScreen();
            showLatestSpending();
            pressEnterToContinue();
            break;
        
        case LOGOUT_BUYER:
            inBuyerLoginMenu = false; 
            break;
        
        default:
            break;
        }
    }

};

void handleSellerLoginMenu(){
    clearScreen();
    bool inSellerLoginMenu = true;

    while (inSellerLoginMenu) {
        clearScreen();
        cout << "\n=========================================================\n";
        cout << "                       Seller MENU\n";
        cout << "=========================================================\n";
        cout << "1. Show Seller Info\n";
        cout << "2. Add Item To Inventory\n";
        cout << "3. Update Detail Item\n";
        cout << "4. Show Inventory\n";
        cout << "5. Show Orders\n";
        cout << "6. Update Order Status\n";
        cout << "7. Show Top Items\n";
        cout << "8. Show Loyal Customers\n";
        cout << "9. Check Seller Balance\n";
        cout << "10. Logout\n";
        cout << "=========================================================\n";
        cout << "Select option (1-10): ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input! Please enter a number (1-4).\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        SellerLoginMenuPrompt sellerLoginMenuPrompt = static_cast<SellerLoginMenuPrompt>(choice - 1);

        switch (sellerLoginMenuPrompt)
        {
        case SHOW_SELLER_INFO:
            clearScreen();
            showSellerInfo();
            pressEnterToContinue();
            break;
        
        case ADD_ITEM:
            clearScreen();
            addItem();
            pressEnterToContinue();
            break;
        
        case UPDATE_ITEM:
            clearScreen();
            updateItem();
            pressEnterToContinue();
            break;
        
        case SHOW_INVENTORY_FOR_SELLER:
            clearScreen();
            showMyInventory();
            pressEnterToContinue();
            break;

        case SHOW_ORDERS:
            clearScreen();
            showAllOrders();
            pressEnterToContinue();
            break;
        
        case UPDATE_ORDER_STATUS:
            clearScreen();
            updateOrderStatus();
            pressEnterToContinue();
            break;
        
        case SHOW_TOP_ITEMS:
            clearScreen();
            mostFrequentMItems();
            pressEnterToContinue();
            break;
        
        case SHOW_LOYAL_CUSTOMERS:
            clearScreen();
            listMostActiveBuyerPerDay();
            pressEnterToContinue();
            break;
        
        case CHECK_BALANCE:
            clearScreen();
            checkSellerBalance();
            pressEnterToContinue();
            break;
        
        case LOGOUT_SELLER:
            inSellerLoginMenu = false;
            break;
        
        default:
            break;
        }
    }

};

void handleBankCapabilitiesMenu(){
    clearScreen();
    bool inBankCapabilities = true;
    while (inBankCapabilities) {
        clearScreen();
        cout << "\n=========================================================\n";
        cout << "                       BANK CAPABILITIES MENU\n";
        cout << "=========================================================\n";
        cout << "1. Show List All Bank Customers\n";
        cout << "2. Search Customers By ID\n";
        cout << "3. Show Latest Week Transaction\n";
        cout << "4. Filter Transaction By Type\n";
        cout << "5. Show Dormant Customers\n";
        cout << "6. Show Top Active Users\n";
        cout << "7. Logout\n";
        cout << "=========================================================\n";
        cout << "Select option (1-7): ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input! Please enter a number (1-4).\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        BankCapabilitiesPrompt bankCapabilitiesPrompt = static_cast<BankCapabilitiesPrompt>(choice - 1);

        switch (bankCapabilitiesPrompt)
        {
        case LIST_ALL_BANK_CUSTOMERS:
            clearScreen();
            listAllBankCustommers();
            pressEnterToContinue();
            break;
        case SEARCH_CUSTOMERS_BY_ID:
            clearScreen();
            searchCustomersById();
            pressEnterToContinue();
            break;
        case SHOW_LATEST_WEEK_TRANSACTION:
            clearScreen();
            listAllTransactionLastWeek();
            pressEnterToContinue();
            break;
        case FILTER_TRANSACTION_BY_TYPE:
            clearScreen();
            filterTransactionByType();
            pressEnterToContinue();
            break;
        case SHOW_DORMANT_CUSTOMERS:
            clearScreen();
            listDormantAccounts();
            pressEnterToContinue();
            break;
        case SHOW_TOP_ACTIVE_USERS:
            clearScreen();
            listTopActiveUsersToday();
            pressEnterToContinue();
            break;
        case LOGOUT_BANK:
            inBankCapabilities = false;
            break;
        default:
            break;
        }

        

    }
}

void handleStoreCapabilitiesMenu(){
    clearScreen();
    bool inStoreCapabilities = true;
    while (inStoreCapabilities) {
        clearScreen();
        cout << "\n=========================================================\n";
        cout << "                       STORE CAPABILITIES MENU\n";
        cout << "=========================================================\n";
        cout << "1. Show List All Transaction Of The Latest K Days\n";
        cout << "2. List All Pending Transactions\n";
        cout << "3. List Most Frequent M Items\n";
        cout << "4. List Most Active Buyers Per Day\n";
        cout << "5. List Most Active Sellers Per Day\n";
        cout << "6. Logout\n";
        cout << "=========================================================\n";
        cout << "Select option (1-6): ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input! Please enter a number (1-4).\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        StoreCapabilitiesPrompt storeCapabilitiesPrompt = static_cast<StoreCapabilitiesPrompt>(choice - 1);

        switch (storeCapabilitiesPrompt)
        {
        case LIST_ALL_TRANSACTION_OF_THE_LATEST_K_DAYS:
            clearScreen();
            listTransactionLatestKDays();
            pressEnterToContinue();
            break;
        case LIST_ALL_PENDING_TRANSACTIONS:
            clearScreen();
            listPendingTransactions();
            pressEnterToContinue();
            break;
        case LIST_MOST_FREQUENT_M_ITEMS:
            clearScreen();
            mostFrequentMItems();
            pressEnterToContinue();
            break;
        case LIST_MOST_ACTIVE_BUYERS_PER_DAY:
            clearScreen();
            listMostActiveBuyerPerDay();
            pressEnterToContinue();
            break;
        case LIST_MOST_ACTIVE_SELLERS_PER_DAY:
            clearScreen();
            listMostActiveSellerPerDay();
            pressEnterToContinue();
            break;
        case LOGOUT_STORE:
            inStoreCapabilities = false;
            break;
        default:
            break;
        }
    }
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
    getline(cin >> ws, name);

    Buyer* foundBuyer = Database::findBuyerByName(name);

    if (foundBuyer != nullptr) {
        Database::loggedBuyer = foundBuyer;
        cout << "\nWelcome back, " << Database::loggedBuyer->getBuyerName() << "!";
        cout << "\nLogin successful!\n";
        handleBuyerLoginMenu();
    } else {
        cout << "\nLogin failed. Buyer with name '" << name << "' not found. Do A Register First\n";
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
        handleSellerLoginMenu();
    } else {
        cout << "\nLogin failed. Seller with name '" << name << "' not found. Do A Register First\n";
    }
}

void handleBankCapabilities() {
    cout << "\n=========================================================\n";
    cout << "                        BANK CAPABILITIES\n";
    cout << "=========================================================\n";

    if (!Database::isBankLinked){
        cout << "Bank Customer Is Not Linked" << endl;
        cout << "Register Bank Customer First" << endl;
        return;
    }
    cout << "\nBank Customer Is Linked. Show Bank Capabilities...\n";
    handleBankCapabilitiesMenu();
}

void handleStoreCapabilities() {
    cout << "\n=========================================================\n";
    cout << "                        STORE CAPABILITIES\n";
    cout << "=========================================================\n";

    handleStoreCapabilitiesMenu();
}

/// =============================================================
/// Menus
/// =============================================================
void handleRegisterMenu() {
    clearScreen();
    bool inRegisterMenu = true;

    while (inRegisterMenu) {
        clearScreen();
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
                clearScreen();
                handleRegisterAsBuyer();
                pressEnterToContinue();
                break;
            

            case REGISTER_AS_SELLER:
                clearScreen();
                handleRegisterAsSeller();
                pressEnterToContinue();
                break;

            case REGISTER_AS_BANK_CUSTOMER:
                clearScreen();
                handleRegisterBankCustomer();
                pressEnterToContinue();
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
        clearScreen();
        cout << "\n=========================================================\n";
        cout << "                       LOGIN MENU\n";
        cout << "=========================================================\n";
        cout << "1. Login As Buyer\n";
        cout << "2. Login As Seller\n";
        cout << "3. Bank Capabilities\n";
        cout << "4. Store Capabilities\n";
        cout << "5. Back To Main Menu\n";
        cout << "=========================================================\n";
        cout << "Select option (1-5): ";

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
            clearScreen();
            handleBuyerLogin();
            pressEnterToContinue();
            break;
        
        case LOGIN_AS_SELLER:
            clearScreen();
            handleSellerLogin();
            pressEnterToContinue();
            break;
        
        case STORE_CAPABILITIES:
            clearScreen();
            handleSellerLogin();
            pressEnterToContinue();
            break;
        
        case BANK_CAPABILITIES:
            clearScreen();
            handleBankCapabilities();
            pressEnterToContinue();
            break;
        
        case LOGIN_BACK:
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
    Database::seedData();
    
    PrimaryPrompt primaryPrompt = MAIN_PROMPT;
    int choice;

    while (primaryPrompt != EXIT_PROGRAM) {
        clearScreen();
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
                clearScreen();
                handleLoginMenu();
                primaryPrompt = MAIN_PROMPT;
                break;

            case REGISTER:
                clearScreen();
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