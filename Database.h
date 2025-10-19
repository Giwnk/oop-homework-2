#if !defined(DATABASE)
#define DATABASE

#include <iostream>
#include <vector>
#include <string>
#include "Headers/Bank.h"
#include "Headers/Buyer.h"
#include "Headers/Seller.h"
#include "Headers/Transaction.h"
#include "Headers/BankTransaction.h"

using namespace std;

class Database{
    public:
    time_t now = time(0);
    const time_t SECONDS_IN_A_DAY = 24 * 60 * 60;

    inline static bool isBuyer = false;
    inline static bool isSeller = false;
    inline static bool isBankLinked = false;

    static vector<Buyer*> listBuyers;
    inline static vector<Seller*> listSellers;
    inline static vector<Store*> listStores;
    inline static vector<Transaction> transactionHistory;
    inline static vector<BankTransaction> bankTransactionHistory;
    inline static Bank mainBank;
    inline static BankCustomer* loggedBankCustomer = nullptr;
    inline static Buyer* loggedBuyer = nullptr;
    inline static Seller* loggedSeller = nullptr;
    inline static Store* newStore = nullptr;


    static Buyer* findBuyerByName(string inputName);
    static Buyer* findBuyerById(int inputId);
    static Seller* findSellerByName(string inputName);
    static Item* findItemById(int itemId, Store*& foundInStore);
    static Transaction* findTransactionById(int transactionId);
    static void addBuyer(Buyer* buyer);
    static void addSeller(Seller* seller);
    static void addStore(Store* store);
    static void addBankCustomer(BankCustomer* customer);

    static void seedData();

};

#endif // DATABASE

