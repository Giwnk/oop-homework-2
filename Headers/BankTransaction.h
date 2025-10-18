#if !defined(BANK_TRANSACTION)
#define BANK_TRANSACTION
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "BankCustomer.h"
using namespace std;

enum TransactionStatus{
    DEPOSIT,
    WITHDRAWAL
};

class BankTransaction{
    private:
    int customerId;
    double totalAmount;
    TransactionStatus status;
    time_t timestamp;

    BankTransaction(int custId, double amt, TransactionStatus txType);

    public:
    static BankTransaction createDeposit(int custId, double amount);
    static BankTransaction createWithdrawal(int custId, double amount);

    int getCustomerId();
    double getAmount();
    TransactionStatus getType();
    time_t getTimestamp();
    string getTypeString();
    void displayTimestamp();
    void printBankReceipt();

};


#endif // BANK_TRANSACTION
