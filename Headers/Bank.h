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

    void addBankCustomer(BankCustomer &inputCustomer){
        listBankCustomers.push_back(inputCustomer);
    }

    void doWithdraw(int inputAmount, int inputCustomerId){
        BankCustomer* CustomerAccount = searchCustomerById(inputCustomerId);
        if (!CustomerAccount)
        {
            cout << "ERROR: Nasabah dengan ID " << inputCustomerId << " tidak ditemukan!" << endl;
            return;
        } else{
            CustomerAccount->withdraw(inputAmount);
        }
    }

    void doDeposit(double inputAmount, int inputCustomerId);
    void doWithdraw(double inputAmount, int inputCustomerId);

    void doTransfer(double inputAmount, int inputCustomerId, int inputDestinateId);

    void showInfoCustomers();

    int getTotalCustomers();

    vector<BankCustomer> getListBankCustomers() {
        return listBankCustomers;
    }
};

#endif // Bank
