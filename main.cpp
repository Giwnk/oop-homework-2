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


/// =============================================================
/// Buyer Login Menu
/// =============================================================

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
    cout << "\n=== LIST STORES ===\n" << endl;
    if (Database::listStores.empty())
    {
        cout << "Store is empty.\n" << endl;
        return;
    }
    for (auto &&store : Database::listStores)
    {
        cout << "======" << store->getStoreName() << "======" << endl; 
        store->showDetailStore();
        cout << "\n" << endl;
    }
}

void showInventory(){
    cout << "\n=== SHOW INVENTORY ===\n" << endl;
    if (Database::listStores.empty())
    {
        cout << "Store is empty.\n" << endl;
        return;
    }
    
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

void showLatestSpending() {
    if (Database::bankTransactionHistory.empty()){
        cout << "Bank Transaction History is empty.\n" << endl;
        return;
    }

    int inputDays;
    cout << "\n=== SHOW LATEST SPENDING ===\n" << endl;
    cout << "Input How Many Days You Want To See: ";
    cin >> inputDays;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    listWithdrawalsLatestKDays(inputDays);

}

/// =============================================================
/// Seller Login Menu
/// =============================================================

void showSellerInfo(){
    Database::loggedSeller->showInfoSeller();
}

void addItem(){
    string itemName;
    int itemPrice, itemQuantity;
    cout << "\n=== ADD ITEM ===\n" << endl;
    cout << "Input Item Name: ";
    getline(cin, itemName);
    cout << "Input Item Price: ";
    cin >> itemPrice;
    cout << "Input Item Quantity: ";
    cin >> itemQuantity;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Item* newItem = new Item(itemName, itemPrice, itemQuantity);
    Database::newStore->addItem(*newItem);
    cout << "\nItem Added Successfully!\n";
}

void updateItem(){
    int inputItemId;
    cout << "\n=== UPDATE ITEM ===\n" << endl;
    cout << "Input ID Item That You Want To Update: ";
    cin >> inputItemId;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Item* foundItem = Database::findItemById(inputItemId, Database::newStore);
    if (foundItem == nullptr)
    {
        cout << "\nItem With ID " << inputItemId << " Not Found In Store.\n" << endl;
        return;
    }

    string itemName;
    int itemPrice, itemQuantity;
    cout << "Input New Item Name: ";
    getline(cin, itemName);
    cout << "Input New Item Price: ";
    cin >> itemPrice;
    cout << "Input New Item Quantity: ";
    cin >> itemQuantity;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    foundItem->setItemName(itemName);
    foundItem->setItemPrice(itemPrice);
    foundItem->addItemQuantity(itemQuantity);
    cout << "\nItem Updated Successfully!\n";
    cout << "\n Detail Item Updated: \n" << endl;
    foundItem->showDetailItem();

}

void showMyInventory(){
    cout << "\n=== SHOW MY INVENTORY ===\n" << endl;
    if (Database::newStore == nullptr)
    {
        cout << "Store is empty.\n" << endl;
        return;
    }
    Database::newStore->showInventory();
}

void updateOrderStatus(){
    cout << "\n=== UPDATE ORDER STATUS ===\n" << endl;
    if (Database::transactionHistory.empty())
    {
        cout << "Transaction History is empty.\n" << endl;
        return;
    }

    int inputTransactionId;
    cout << "\n=== UPDATE ORDER STATUS ===\n" << endl;
    cout << "Input ID Transaction That You Want To Update: ";
    cin >> inputTransactionId;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Transaction* foundTransaction = Database::findTransactionById(inputTransactionId);
    if (foundTransaction == nullptr)
    {
        cout << "\nTransaction With ID " << inputTransactionId << " Not Found.\n" << endl;
        return;
    }

    string newOrderStatus;
    cout << "Input New Order Status: ";
    getline(cin, newOrderStatus);

    foundTransaction->setStatus(newOrderStatus);
    cout << "\nOrder Status Updated Successfully!\n";
    cout << "\n Detail Order Updated: \n" << endl;
    foundTransaction->printReceipt();
    cout << "\n" << endl;

}

void showTopItems(){
    if (Database::transactionHistory.empty())
    {
        cout << "Transaction History is empty.\n" << endl;
        return;
    }

    int inputMItems;
    cout << "\n=== SHOW TOP ITEMS ===\n" << endl;
    cout << "Input M Items: ";
    cin >> inputMItems;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    mostFrequentMItems(inputMItems);
}

void checkSellerBalance(){
    cout << "\n=== CHECK SELLER BALANCE ===\n" << endl;
    Database::loggedSeller->getBuyerAccount()->showInfo();
}    

/// =============================================================
/// Bank Capabilities
/// =============================================================

void listAllBankCustommers(){
    if (Database::mainBank.getListBankCustomers().empty())
    {
        cout << "Bank Customer is empty.\n" << endl;
        return;
    }
    
    cout << "\n=== LIST ALL BANK CUSTOMERS ===\n" << endl;
    for (auto &&bankCustomer : Database::mainBank.getListBankCustomers())
    {
        bankCustomer.showInfo();
    }
}

void searchCustomersById(){
    int inputId;
    cout << "\n=== SEARCH CUSTOMERS BY ID ===\n" << endl;
    cout << "Input ID Bank Customer That You Want To Search: ";
    cin >> inputId;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    BankCustomer* foundBankCustomer = Database::mainBank.searchCustomerById(inputId);
    if (foundBankCustomer == nullptr)
    {
        cout << "\nBank Customer With ID " << inputId << " Not Found.\n" << endl;
        return;
    }
    foundBankCustomer->showInfo();
}

void filterTransactionByType(){
    string inputTypeFilter;
    cout << "\n=== FILTER BANK TRANSACTION BY TYPE ===\n" << endl;
    cout << "Choose transaction Type (1: Deposit, 2: Withdrawal): ";
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string filterType;
    if (choice == 1) {
        filterType = "Deposit";
    } else if (choice == 2) {
        filterType = "Withdrawal";
    } else {
        cout << "Invalid choice. Please enter 1 or 2\n";
        return;
    }

    cout << "\n--- Menampilkan semua transaksi '" << filterType << "' ---\n";
    bool isFound = false;
    for (auto& transaction : Database::bankTransactionHistory) {
        if (transaction.getTypeString() == filterType) {
            transaction.printBankReceipt();
            cout << "--------------------------------\n";
            isFound = true;
        }
    }
    if (!isFound) {
        cout << "No transactions found with type'" << filterType << "' .\n" << endl;;
    }
}

void listDormantAccounts() {
    cout << "\n=== LIST DORMANT ACCOUNTS (Inactive > 30 Days) ===\n";
    time_t now = time(0);
    time_t cutoffTime = now - (30L * 24 * 60 * 60);
    bool anyDormantFound = false;

    for (auto& customer : Database::mainBank.getListBankCustomers()) {
        bool hasRecentTransaction = false;
        for (auto& transaction : Database::bankTransactionHistory) {
            if (transaction.getCustomerId() == customer.getId() && transaction.getTimestamp() >= cutoffTime) {
                hasRecentTransaction = true; // Ditemukan transaksi baru! Akun ini aktif.
                break; // Tidak perlu cek transaksi lain untuk nasabah ini
            }
        }

        // Jika setelah dicek semua, tidak ada transaksi baru, berarti dormant
        if (!hasRecentTransaction) {
            cout << "Acount Dormant Found:\n";
            customer.showInfo();
            cout << "--------------------------------\n";
            anyDormantFound = true;
        }
    }

    if (!anyDormantFound) {
        cout << "There Is No Dormant Accounts.\n";
    }
}

void listTopActiveUsersToday() {
    cout << "\n=== LIST TOP ACTIVE USERS TODAY ===\n";
    
    int topN;
    cout << "How many top users do you want to display? ";
    while (!(cin >> topN) || topN <= 0) {
        cout << "Invalid input. Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    time_t now = time(0);
    tm* localtm = localtime(&now);
    localtm->tm_hour = 0; localtm->tm_min = 0; localtm->tm_sec = 0;
    time_t startOfToday = mktime(localtm);
    
    map<int, int> buyerActivity;

    for (auto& transaction : Database::transactionHistory) {
        if (transaction.getTransactionTime() >= startOfToday) {
            buyerActivity[transaction.getBuyerId()]++;
        }
    }

    if (buyerActivity.empty()) {
        cout << "No transactions have occurred today.\n" << endl;
        return;
    }

    vector<pair<int, int>> sortedBuyers(buyerActivity.begin(), buyerActivity.end());
    sort(sortedBuyers.begin(), sortedBuyers.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; // Urutkan berdasarkan jumlah transaksi (value)
    });

    cout << "\n--- Top " << topN << " Most Active Users by Transaction Count ---\n";
    int rank = 1;
    for (const auto& buyerPair : sortedBuyers) {
        if (rank > topN) break;

        int buyerId = buyerPair.first;
        int transactionCount = buyerPair.second;
        
        Buyer* buyer = Database::findBuyerById(buyerId);
        string buyerName = (buyer != nullptr) ? buyer->getBuyerName() : "Unknown Buyer";

        cout << rank << ". " << buyerName << " (ID: " << buyerId << ")\n";
        cout << "   -> " << transactionCount << " transactions\n";
        rank++;
    }
    cout << "-----------------------------------------------------\n\n";
}




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

        case SHOW_INVENTORY_FOR_BUYER:
            showInventory();
            break;
        
        case PURCHASE_ITEM:
            purchaseItem();
            break;
        
        case SHOW_ALL_ORDERS:
            showAllOrders();
            break;
        
        case SHOW_LATEST_SPENDING:
            showLatestSpending();
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
    bool inSellerLoginMenu = true;

    while (inSellerLoginMenu) {
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
            showSellerInfo();
            break;
        
        case ADD_ITEM:
            addItem();
            break;
        
        case UPDATE_ITEM:
            updateItem();
            break;
        
        case SHOW_INVENTORY_FOR_SELLER:
            showMyInventory();
            break;

        case SHOW_ORDERS:
            showAllOrders();
            break;
        
        case UPDATE_ORDER_STATUS:
            updateOrderStatus();
            break;
        
        case SHOW_TOP_ITEMS:
            showTopItems();
            break;
        
        case SHOW_LOYAL_CUSTOMERS:
            listMostActiveBuyerPerDay();
            break;
        
        case CHECK_BALANCE:
            checkSellerBalance();
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
    bool inBankCapabilities = true;
    while (inBankCapabilities) {
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
        cout << "Select option (1-10): ";

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
            listAllBankCustommers();
            break;
        case SEARCH_CUSTOMERS_BY_ID:
            searchCustomersById();
            break;
        case SHOW_LATEST_WEEK_TRANSACTION:
            listAllTransactionLastWeek();
            break;
        case FILTER_TRANSACTION_BY_TYPE:
            filterTransactionByType();
            break;
        case SHOW_DORMANT_CUSTOMERS:
            listDormantAccounts();
            break;
        case SHOW_TOP_ACTIVE_USERS:
            listTopActiveUsersToday();
            break;
        case LOGOUT_BANK:
            inBankCapabilities = false;
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
        handleSellerLoginMenu();
    } else {
        cout << "\nLogin failed. Seller with name '" << name << "' not found.\n";
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
        
        case STORE_CAPABILITIES:
            handleSellerLogin();
            break;
        
        case BANK_CAPABILITIES:
            handleBankCapabilities();
            break;
        
        case LOGOUT_BUYER:
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