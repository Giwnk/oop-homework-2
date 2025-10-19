#ifndef BANK_CUSTOMER
#define BANK_CUSTOMER
#include <iostream>
#include <vector>
#include <string>
#include "BankTransaction.h"
using namespace std;


class BankTransaction;

class BankCustomer{
    private:
    int static inline idBankCustomerCounter;
    int id;
    string name;
    double balance;
    vector<BankTransaction> listbankTransaction;

    public:
    BankCustomer(string inputName, double inputBalance);

    int getId();
    string getName();
    int getBalance();

    bool withdraw(double inputAmount);
    void deposit(double inputAmount);

    void showInfo();
    void showAllReceipt();
    vector<BankTransaction> getBankTransactionHistory();
};

#endif