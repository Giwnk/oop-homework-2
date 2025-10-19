#ifndef BUYER
#define BUYER

#include <iostream>
#include <vector>
#include <string>
#include "BankCustomer.h"
#include "Transaction.h"
#include "BankTransaction.h"
#include "Store.h"

using namespace std;


class Seller;

class Buyer{
    private:
    inline static int buyerIdCounter = 100;
    int id; 
    string name, email, address, phoneNumber;
    BankCustomer& customerAccount;

    int inputItemId = 0, inputQuantity = 0;
    Store* targetStore = nullptr;

    public:
    Buyer(string inputName, string inputEmail, string inputAddress, string inputPhoneNum, BankCustomer* inputCustomer);
    int getBuyerID(){return id;}
    string getBuyerPhoneNum(){return phoneNumber;}
    string getBuyerName(){return name;}
    string getBuyerEmail(){return email;}
    string getBuyerAddress(){return address;}
    BankCustomer* getBuyerAccount(){return &customerAccount;}
    

    void purchaseItem(int inputItemId, int inputQuantity, Store* inputStore, Seller* inputSeller, vector<Transaction>* transactionHistory);

    void showInfoBuyer();

};

#endif // Buyer
