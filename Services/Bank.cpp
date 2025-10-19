#include <iostream>
#include <vector>
#include <string>
#include "../Headers/Bank.h"
#include "../Headers/BankCustomer.h"
#include "../Headers/BankTransaction.h"

using namespace std;

BankCustomer* Bank::searchCustomerById(int inputId){
        for (auto &&customer : listBankCustomers)
        {
            if (customer.getId() == inputId)
            {
                return &customer;
            }
        }
        return nullptr;
    }

    void Bank::doWithdraw(double inputAmount, int inputCustomerId){
        BankCustomer* CustomerAccount = searchCustomerById(inputCustomerId);
        // int customerId = CustomerAccount->getId();
        if (!CustomerAccount)
        {
            cout << "ERROR: Nasabah dengan ID " << inputCustomerId << " tidak ditemukan!" << endl;
            return;
        } else{
            CustomerAccount->withdraw(inputAmount);
        }
    }

    void Bank::doDeposit(double inputAmount, int inputCustomerId){
        BankCustomer* CustomerAccount = searchCustomerById(inputCustomerId);
        // int customerId = CustomerAccount->getId();
        if (!CustomerAccount)
        {
            cout << "ERROR: Nasabah dengan ID " << inputCustomerId << " tidak ditemukan!" << endl;
            return;
        } else{
            CustomerAccount->deposit(inputAmount);
        }
    }

    void Bank::doTransfer(double inputAmount, int inputCustomerId, int inputDestinateId){
        BankCustomer* customerAccount = searchCustomerById(inputCustomerId);
        BankCustomer* destinateAccount = searchCustomerById(inputDestinateId);
        customerAccount->withdraw(inputAmount);
        destinateAccount->deposit(inputAmount);
    }

    void Bank::showInfoCustomers(){
        for (auto &&customer : listBankCustomers)
        {
            customer.showInfo();
        }
    }

    void Bank::addBankCustomer(BankCustomer &inputCustomer){
        listBankCustomers.push_back(inputCustomer);
    }

    int Bank::getTotalCustomers(){
        int totalCustomers = listBankCustomers.size();
        return totalCustomers;
    }

    vector<BankCustomer> Bank::getListBankCustomers() {
        return listBankCustomers;
    }

