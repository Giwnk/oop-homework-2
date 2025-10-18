#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "../Headers/Transaction.h"
using namespace std;

Transaction::Transaction(double inputAmount, int inputBuyerId, int inputSellerId, int inputItemId, int inputQuantity, string inputItemName, string inputStoreName)
        : transactionAmount(inputAmount), buyerId(inputBuyerId), sellerId(inputSellerId), itemId(inputItemId), quantity(inputQuantity), itemName(inputItemName), storeName(inputStoreName) {
        transactionTime = time(0); // Catat waktu transaksi
        orderStatus = PAID;
    }
Transaction::Transaction(double inputAmount, int inputBuyerId, int inputSellerId, int inputItemId, int inputQuantity, string inputItemName, string inputStoreName, time_t inputTransactionTime)
        : transactionAmount(inputAmount), buyerId(inputBuyerId), sellerId(inputSellerId), itemId(inputItemId), quantity(inputQuantity), itemName(inputItemName), storeName(inputStoreName) {
        transactionTime = inputTransactionTime; // Catat waktu transaksi
        orderStatus = PAID;
    }

    time_t Transaction::getTransactionTime(){
        return transactionTime;
    }

    string Transaction::getOrderStatus(){
        switch (orderStatus) {
        case PAID:
            return "Paid"; // Jika statusnya PAID, kembalikan string "Paid"
        case COMPLETED:
            return "Completed";
        case CANCELLED:
            return "Cancelled";
        default:
            return "Unknown"; // Untuk keamanan jika ada status lain
    }
    }

    void Transaction::setStatus(OrderStatus inputStatus){
        orderStatus = inputStatus;
    }

    int Transaction::getBuyerId(){return buyerId;}
    int Transaction::getSellerId(){return sellerId;}
    int Transaction::getItemId(){return itemId;}
    string Transaction::getItemName(){return itemName;}


    void Transaction::displayTimestamp(){
        char* printTime = ctime(&transactionTime);

        cout << "["; 
        
        for (int i = 0; printTime[i] != '\0'; ++i) {
            if (printTime[i] != '\n') {
                cout << printTime[i];
            }
        }
        cout << "]" << endl;
    }

    void Transaction::printReceipt() {
        cout << "\n--- Struk Transaksi ---" << endl;
        cout << "Waktu dan Tanggal: ";
        displayTimestamp();
        cout << "Pembeli: " << buyerId << endl;
        cout << "Penjual: " << sellerId << " (" << storeName << ")" << endl;
        cout << "Item: " << itemName << " (ID: " << itemId << ")" << endl;
        cout << "Jumlah: " << quantity << endl;
        cout << "Total Harga: Rp " << transactionAmount << endl;
        cout << "-----------------------" << endl;
    }