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

    public:
    Buyer(string inputPhoneNum, string inputName, string inputEmail, string inputAddress, BankCustomer* inputCustomer) 
    : id(++buyerIdCounter), phoneNumber(inputPhoneNum), name(inputName),email(inputEmail),address(inputAddress),customerAccount(*inputCustomer){}

    int getBuyerID(){return id;}
    string getBuyerPhoneNum(){return phoneNumber;}
    string getBuyerName(){return name;}
    string getBuyerEmail(){return email;}
    string getBuyerAddress(){return address;}
    BankCustomer* getBuyerAccount(){return &customerAccount;}
    

    void purchaseItem(int inputItemId, int inputQuantity, Store* inputStore, Seller* inputSeller, vector<Transaction>* transactionHistory);

    void showInfoBuyer(){
        cout << "\n========================" << endl;
        cout << ">>> == BUYER INFO == <<< " << endl;
        cout << "========================\n" << endl;
        cout << "Buyer ID: " << getBuyerID() << endl;
        cout << "Buyer Name: " << getBuyerName() << endl;
        cout << "Buyer Email: " << getBuyerEmail() << endl;
        cout << "Buyer Phone Number: " << getBuyerPhoneNum() << endl;
        cout << "Buyer Address: " << getBuyerAddress() << endl;
        
            cout << "This Buyer linked with Bank Account" << endl;
            customerAccount.showInfo();
            cout << "\n" << endl;
        
    }

};

#endif // Buyer
