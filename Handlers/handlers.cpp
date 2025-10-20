#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <tuple>
#include <ctime>
#include <limits>
#include "Handlers/handlers.h"
using namespace std;

/// =============================================================
// Utility Handlers
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pressEnterToContinue() {
    cout << "\nPress ENTER to continue...";
    // Perintah ini akan membersihkan sisa input JIKA ADA,
    // atau akan MENUNGGU input Enter JIKA buffer bersih.
    // Sangat aman dan serbaguna.
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string time_t_to_date_string(time_t timeValue) {
    char buffer[11];
    tm* timeinfo = localtime(&timeValue);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    return string(buffer);
}

/// =============================================================
// Store Handlers

void listTransactionLatestKDays(){
    int inputKDays;
    cout << "\n=== Show Latest Transaction In The Latest K Days ===\n";
    if (Database::transactionHistory.empty())
    {
        cout << "Transaction History is empty.\n" << endl;
        pressEnterToContinue();
        return;
    }

    cout << "How Many Days You Want To See: ";
    cin >> inputKDays;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (inputKDays <= 0)
    {
        cout << "Invalid Input. Input Must Larger Than 0.\n" << endl;
        pressEnterToContinue();
        return;
    }


    time_t now = time(0);
    time_t cutoffTime = now - (inputKDays * 24 * 60 * 60);

    bool isFound = false;
    for (auto &&transaction : Database::transactionHistory)
    {
        if (transaction.getTransactionTime() >= cutoffTime)
        {
            transaction.printReceipt();
            isFound = true;
        } 
    }
    if (!isFound)
    {
        cout << "No transactions found within the last " << inputKDays << " days." << endl;
        
    }
}

void listPendingTransactions(){
    bool isFound = false;
    for (auto &&transaction : Database::transactionHistory)
    {
        if (transaction.getOrderStatus() == "Paid")
        {
            transaction.printReceipt();
            isFound = true;
        }
    }

    if (!isFound)
    {
        cout << "No pending transactions found!" << endl;
    }
}

void mostFrequentMItems(){
    if (Database::transactionHistory.empty())
    {
        cout << "Transaction History is empty.\n" << endl;
        pressEnterToContinue();
        return;
    }

    int inputMItems;
    cout << "\n=== Show Most Frequent M Items ===\n";

    cout << "How Many Items You Want To See: ";
    cin >> inputMItems;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (inputMItems <= 0)
    {
        cout << "Invalid Input. Input Must Larger Than 0.\n" << endl;
        return;
    }

    map<int, pair<string, int>> itemFrequency;

    for (auto &&transaction : Database::transactionHistory){
        int itemId = transaction.getItemId();
        string itemName = transaction.getItemName();

        if (itemFrequency.find(itemId) == itemFrequency.end())
        {
            itemFrequency[itemId] = make_pair(itemName, 1);
        } else{
            itemFrequency[itemId].second++;
        }
    }

    if (itemFrequency.empty()) {
        cout << "No Transactions Found.\n" << endl;
        pressEnterToContinue();
        return;
    }

    vector<tuple<int, string, int>> sortedItems;
    for (auto &&i : itemFrequency)
    {
        int itemId = i.first;
        string itemName = i.second.first;
        int frequency = i.second.second;
        sortedItems.emplace_back(frequency, itemName, itemId);
    }

    sort(sortedItems.begin(), sortedItems.end(), greater<>());

    cout << "\n--- Top " << inputMItems << " Most Frequent Items  ---\n";
    int itemsToShow = min(static_cast<int>(sortedItems.size()), inputMItems);

    for (int i = 0; i < itemsToShow; ++i) {
        int frequency = get<0>(sortedItems[i]);
        string name = get<1>(sortedItems[i]);
        int id = get<2>(sortedItems[i]);
        
        cout << (i + 1) << ". " << name << " (ID: " << id << ")\n";
        cout << "   -> Bought As : " << frequency << " Times\n";
    }
}

void listMostActiveBuyerPerDay() {
    cout << "\n=== MOST ACTIVE BUYER PER DAY ===\n";
    map<string, map<int, int>> dailyActivity;

    for (auto& transaction : Database::transactionHistory) {
        string date = time_t_to_date_string(transaction.getTransactionTime());
        int buyer = transaction.getBuyerId();
        dailyActivity[date][buyer]++;
    }

    if (dailyActivity.empty()) {
        cout << "No transactions found for analysis.\n";
        cout << "------------------------------------------\n\n";
        pressEnterToContinue();
        return;
    }

    for ( auto& dayPair : dailyActivity) {
        string date = dayPair.first;
        map<int, int> buyerCounts = dayPair.second;

        int topBuyerId = -1;
        int maxTransactions = 0;

        for (auto& buyerPair : buyerCounts) {
            int buyerId = buyerPair.first;
            int count = buyerPair.second;

            if (count > maxTransactions) {
                maxTransactions = count;
                topBuyerId = buyerId;
            }
        }


        cout << "-> On " << date << ", Most Active Buyer is ID "
             << topBuyerId << " with " << maxTransactions << " Transaction.\n";
    }
}

void listMostActiveSellerPerDay() {
    cout << "\n=== MOST ACTIVE SELLER PER DAY ===\n";
    map<string, map<int, int>> dailyActivity;

    for (auto& transaction : Database::transactionHistory) {
        string date = time_t_to_date_string(transaction.getTransactionTime());
        int seller = transaction.getSellerId();
        dailyActivity[date][seller]++;
    }

    if (dailyActivity.empty()) {
        cout << "No transactions found for analysis.\n";
        cout << "------------------------------------------\n\n";
        pressEnterToContinue();
        return;
    }

    for ( auto& dayPair : dailyActivity) {
        string date = dayPair.first;
        map<int, int> sellerCounts = dayPair.second;

        int topSellerId = -1;
        int maxTransactions = 0;

        for (const auto& sellerPair : sellerCounts) {
            int sellerId = sellerPair.first;
            int count = sellerPair.second;

            if (count > maxTransactions) {
                maxTransactions = count;
                topSellerId = sellerId;
            }
        }


        cout << "-> On " << date << ", Most Active Seller is ID "
             << topSellerId << " With " << maxTransactions << " Transaction.\n";
    }
    cout << "------------------------------------------\n\n";
    pressEnterToContinue();
}

/// =============================================================
// Bank Handlers
void listAllTransactionLastWeek(){
    time_t now = time(0);
    time_t cutoffTime = now - (7 * 24 * 60 * 60);

    bool isFound = false;
    for (auto &&transaction : Database::bankTransactionHistory)
    {
        if (transaction.getTimestamp() >= cutoffTime)
        {
            transaction.printBankReceipt();
            isFound = true;
        } 
    }
    if (!isFound)
    {
        cout << "No transactions found within the last weeks " << endl;
    }
}

void listWithdrawalsLatestKDays(int inputKDays) {
    time_t now = time(0);
    time_t cutoffTime = now - (static_cast<time_t>(inputKDays) * 24 * 60 * 60);

    cout << "\n=== Show Latest Spending In The Last " << inputKDays << " Days ===\n";

    bool isFound = false;
    for ( auto& bankTransaction : Database::bankTransactionHistory) {
        
        
        if (bankTransaction.getTimestamp() >= cutoffTime && 
            bankTransaction.getTypeString() == "Withdrawal") 
        {
            bankTransaction.printBankReceipt();
            cout << "----------------------------------------\n";
            isFound = true;
        } 
    }

    if (!isFound) {
        cout << "No Transaction Found In The Last" 
             << inputKDays << " Days." << endl;
    }
}

void listAllBankCustommers(){
    if (Database::mainBank.getListBankCustomers().empty())
    {
        cout << "Bank Customer is empty.\n" << endl;
        pressEnterToContinue();
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
        cout << "-----------------------------------------------------\n\n";
        pressEnterToContinue();
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
        pressEnterToContinue();
        return;
    }

    cout << "\n--- Show Transactions With Type'" << filterType << "' ---\n";
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
                break;
            }
        }

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
        pressEnterToContinue();
        return;
    }

    vector<pair<int, int>> sortedBuyers(buyerActivity.begin(), buyerActivity.end());
    sort(sortedBuyers.begin(), sortedBuyers.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
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
}

/// =============================================================
/// Buyer Handlers
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
        Database::loggedSeller = new Seller( name, email, address, phoneNum, Database::loggedBankCustomer, storeName, Database::newStore);
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
        pressEnterToContinue();
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
        pressEnterToContinue();
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
    cout << "Input Item Quantity That You Want To Purchase: ";
    cin >> inputQuantity;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Store* targetStore = nullptr;
    Item* foundItem = Database::findItemById(inputItemId, targetStore);
    if (foundItem == nullptr)
    {
        cout << "\nItem With ID " << inputItemId << " Not Found In Any Store.\n" << endl;
        pressEnterToContinue();
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
        cout << "\nNo Transaction Found With Status '" << inputStatusFilter << "'\n" << endl;
    }

    
}

void showLatestSpending() {
    if (Database::bankTransactionHistory.empty()){
        cout << "Bank Transaction History is empty.\n" << endl;
        pressEnterToContinue();
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
/// Seller Handlers
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
    Database::newStore->addItem(newItem);
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
        pressEnterToContinue();
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
        pressEnterToContinue();
        return;
    }
    Database::newStore->showInventory();
}

void updateOrderStatus(){
    cout << "\n=== UPDATE ORDER STATUS ===\n" << endl;
    if (Database::transactionHistory.empty())
    {
        cout << "Transaction History is empty.\n" << endl;
        pressEnterToContinue();
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
        pressEnterToContinue();
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

void checkSellerBalance(){
    cout << "\n=== CHECK SELLER BALANCE ===\n" << endl;
    Database::loggedSeller->getBuyerAccount()->showInfo();
}    

/// =============================================================