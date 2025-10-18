#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <tuple>
#include <ctime>
#include "../Services/Buyer.cpp"
#include "../Services/BankCustomer.cpp"
#include "../Services/Bank.cpp"
#include "../Services/Item.cpp"
#include "../Services/Store.cpp"
#include "../Services/Seller.cpp"
#include "../Services/Transaction.cpp"
#include "../Services/BankTransaction.cpp"
#include "../Database.cpp"
using namespace std;


// Helper Function
string time_t_to_date_string(time_t timeValue) {
    char buffer[11];
    tm* timeinfo = localtime(&timeValue);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    return string(buffer);
}

// Store Handlers

void listTransactionLatestKDays(int inputKDays){
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
        if (transaction.getOrderStatus() == OrderStatus::PAID)
        {
            transaction.printReceipt();
            bool isFound = true;
        }
    }

    if (!isFound)
    {
        cout << "No pending transactions found!" << endl;
    }
}

void mostFrequentMItems(int inputMItems){
    if (inputMItems <= 0)
    {
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
    int itemsToShow = min((int)sortedItems.size(), inputMItems);

    for (int i = 0; i < itemsToShow; ++i) {
        int frequency = get<0>(sortedItems[i]);
        string name = get<1>(sortedItems[i]);
        int id = get<2>(sortedItems[i]);
        
        cout << (i + 1) << ". " << name << " (ID: " << id << ")\n";
        cout << "   -> Bought As : " << frequency << " Times\n";
    }
    cout << "----------------------------------------------\n\n";
    
}

void listMostActiveBuyerPerDay() {
    cout << "\n--- Laporan Pembeli Teraktif per Hari ---\n";
    map<string, map<int, int>> dailyActivity;

    for (auto& transaction : Database::transactionHistory) {
        string date = time_t_to_date_string(transaction.getTransactionTime());
        int buyer = transaction.getBuyerId();
        dailyActivity[date][buyer]++;
    }

    if (dailyActivity.empty()) {
        cout << "Belum ada transaksi untuk dianalisis.\n";
        cout << "------------------------------------------\n\n";
        return;
    }

    for ( auto& dayPair : dailyActivity) {
        string date = dayPair.first;
        map<int, int> buyerCounts = dayPair.second;

        int topBuyerId = -1;
        int maxTransactions = 0;

        for (const auto& buyerPair : buyerCounts) {
            int buyerId = buyerPair.first;
            int count = buyerPair.second;

            if (count > maxTransactions) {
                maxTransactions = count;
                topBuyerId = buyerId;
            }
        }


        cout << "-> Pada tanggal " << date << ", pembeli teraktif adalah ID "
             << topBuyerId << " dengan " << maxTransactions << " transaksi.\n";
    }
    cout << "------------------------------------------\n\n";
}

void listMostActiveSellerPerDay() {
    cout << "\n--- Laporan Penual Teraktif per Hari ---\n";
    map<string, map<int, int>> dailyActivity;

    for (auto& transaction : Database::transactionHistory) {
        string date = time_t_to_date_string(transaction.getTransactionTime());
        int seller = transaction.getSellerId();
        dailyActivity[date][seller]++;
    }

    if (dailyActivity.empty()) {
        cout << "Belum ada transaksi untuk dianalisis.\n";
        cout << "------------------------------------------\n\n";
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


        cout << "-> Pada tanggal " << date << ", pembeli teraktif adalah ID "
             << topSellerId << " dengan " << maxTransactions << " transaksi.\n";
    }
    cout << "------------------------------------------\n\n";
}



// Handlers Bank

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


