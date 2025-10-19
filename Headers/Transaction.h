#if !defined(TRANSASCTION)
#define TRANSASCTION
#include <iostream>
#include <string>
#include <ctime>
using namespace std;


enum OrderStatus{
    PAID,
    COMPLETED,
    CANCELLED
};


class Transaction {
private:
    int transactionId;
    int static transactionIdCounter;
    double transactionAmount;
    int buyerId, sellerId, itemId, quantity;
    string itemName, storeName;
    time_t transactionTime;
    OrderStatus orderStatus;


public:
    Transaction(double inputAmount, int inputBuyerId, int inputSellerId, int inputItemId, int inputQuantity, string inputItemName, string inputStoreName);
    Transaction(double inputAmount, int inputBuyerId, int inputSellerId, int inputItemId, int inputQuantity, string inputItemName, string inputStoreName, time_t inputTransactionTime);

    time_t getTransactionTime();
    string getOrderStatus();

    void setStatus(string inputStatus);

    int getItemId();
    int getBuyerId();
    int getSellerId();
    string getItemName();
    int getTransactionId();


    void displayTimestamp();

    void printReceipt();
};

#endif // TRANSACTION_H
