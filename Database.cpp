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

    inline static vector<Buyer*> listBuyers;
    inline static vector<Seller*> listSellers;
    inline static vector<Store> listStores;
    inline static vector<Transaction> transactionHistory;
    inline static vector<BankTransaction> bankTransactionHistory;
    inline static Bank mainBank;
    inline static BankCustomer* loggedBankCustomer = nullptr;
    inline static Buyer* loggedBuyer = nullptr;
    inline static Seller* loggedSeller = nullptr;
    inline static Store* newStore = nullptr;


    static Buyer* findBuyerByName(string inputName){
        for (auto &&buyer : listBuyers)
        {
            if (buyer->getBuyerName() == inputName)
            {
                return buyer;
            }
            
        }
        return nullptr;
    }

    static Seller* findSellerByName(string inputName){
        for (auto &&seller : listSellers)
        {
            if (seller->getBuyerName() == inputName)
            {
                return seller;
            }
            
        }
        return nullptr;
    }

    static void addBuyer(Buyer* buyer) {
        listBuyers.push_back(buyer); // Menambahkan pointer buyer ke akhir vector 'buyers'
    }
    static void addSeller(Seller* seller) {
        listSellers.push_back(seller); // Menambahkan pointer buyer ke akhir vector 'buyers'
    }

};

#endif // DATABASE

