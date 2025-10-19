#ifndef BANK
#define BANK
#include <iostream>
#include <vector>
#include <string>
#include "BankCustomer.h"
#include "BankTransaction.h"
using namespace std;

class Bank{
    private:
    vector<BankCustomer> listBankCustomers;

    public:
    BankCustomer* searchCustomerById(int inputId);

    void addBankCustomer(BankCustomer &inputCustomer);

    void doDeposit(double inputAmount, int inputCustomerId);
    void doWithdraw(double inputAmount, int inputCustomerId);

    void doTransfer(double inputAmount, int inputCustomerId, int inputDestinateId);

    void showInfoCustomers();

    int getTotalCustomers();

    vector<BankCustomer> getListBankCustomers();
};

#endif // Bank
