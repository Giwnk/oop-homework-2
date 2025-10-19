#include <iostream>
#include <vector>
#include <string>
#include "../Headers/Bank.h"
#include "../Headers/BankCustomer.h"
using namespace std;

    BankCustomer::BankCustomer(string inputName, double inputBalance){
        id = ++idBankCustomerCounter;
        name = inputName;
        balance = inputBalance;
    }

    int BankCustomer::getId(){ return id; }
    string BankCustomer::getName(){ return name; }
    int BankCustomer::getBalance(){ return balance; }

    bool BankCustomer::withdraw(double inputAmount){
        int customerId = id;
        if (inputAmount > 0 && inputAmount <= balance) {
            balance -= inputAmount;
            listbankTransaction.push_back(BankTransaction::createWithdrawal(customerId, inputAmount));
            cout << "Penarikan berhasil." << endl;
            return true; // Transaksi berhasil
        } else {
            cout << "Penarikan gagal. Saldo tidak mencukupi atau jumlah tidak valid." << endl;
            return false; // Transaksi gagal
        }
    }

    void BankCustomer::deposit(double inputAmount){
        int customerId = id;
        if (inputAmount > 0) {
            balance += inputAmount;
            listbankTransaction.push_back(BankTransaction::createDeposit(customerId, inputAmount));
            cout << "Deposit berhasil." << endl;
        } else {
            cout << "Deposit gagal. Jumlah harus positif." << endl;
        }
    }

    void BankCustomer::showInfo(){
        cout << "\nInfo Akun Bank" << endl;
        cout << "Id Akun: " << getId() << endl;
        cout << "Nama Akun: " << getName() << endl;
        cout << "Saldo Akun: " << getBalance() << endl;
    }

    void BankCustomer::showAllReceipt(){
        for (auto &&i : listbankTransaction)
        {
            i.printBankReceipt();
        }
        
    }

    vector<BankTransaction> BankCustomer::getBankTransactionHistory(){
        return listbankTransaction;
    }


