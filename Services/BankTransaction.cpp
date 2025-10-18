#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "../Headers/BankTransaction.h"

// Implementasi Constructor private
BankTransaction::BankTransaction(int custId, double amt, TransactionStatus txType)
        : customerId(custId), totalAmount(amt), status(txType) {
        timestamp = time(0);
    }

// Implementasi "Tombol" Buat Deposit
BankTransaction BankTransaction::createDeposit(int custId, double amount) {
    // Tambahan: pastikan jumlahnya tidak negatif untuk keamanan
    if (amount < 0) {
        throw invalid_argument("Jumlah deposit tidak boleh negatif.");
    }
    // Panggil constructor private dengan tipe yang benar
    return BankTransaction(custId, amount, TransactionStatus::DEPOSIT);
}

// Implementasi "Tombol" Buat Withdrawal
BankTransaction BankTransaction::createWithdrawal(int custId, double amount) {
    // Tambahan: pastikan jumlahnya tidak negatif untuk keamanan
    if (amount < 0) {
        throw invalid_argument("Jumlah withdrawal tidak boleh negatif.");
    }
    // Panggil constructor private dengan tipe yang benar
    return BankTransaction(custId, amount, TransactionStatus::WITHDRAWAL);
}

// Implementasi Getters (tidak ada perubahan)
int BankTransaction::getCustomerId(){ return customerId; }
double BankTransaction::getAmount(){ return totalAmount; }
TransactionStatus BankTransaction::getType(){ return status; }
time_t BankTransaction::getTimestamp(){ return timestamp; }
string BankTransaction::getTypeString() {
    if (status == TransactionStatus::DEPOSIT){
        return "DEPOSIT";
    } 
    else {return "WITHDRAWAL";}
}

void BankTransaction::displayTimestamp(){
        char* printTime = ctime(&timestamp);

        cout << "["; 
        
        for (int i = 0; printTime[i] != '\0'; ++i) {
            if (printTime[i] != '\n') {
                cout << printTime[i];
            }
        }
        cout << "]" << endl;
    }


void BankTransaction::printBankReceipt(){
    cout << "\n--- Struk Transaksi ---" << endl;
        cout << "Waktu dan Tanggal: ";
        displayTimestamp();
        cout << "Customer ID: " << getCustomerId() << endl;
        cout << "Amount: " << getAmount() << endl;
        cout << "Transaction Status: " << getTypeString() << endl;
        cout << "-----------------------" << endl;
}