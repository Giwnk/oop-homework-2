#include <iostream>
#include <vector>
#include <string>
#include "Database.h"

using namespace std;

    Buyer* Database::findBuyerByName(string inputName){
        for (auto &&buyer : listBuyers)
        {
            if (buyer->getBuyerName() == inputName)
            {
                return buyer;
            }
            
        }
        return nullptr;
    }

    Buyer* Database::findBuyerById(int inputId){
        for (auto &&buyer : listBuyers)
        {
            if (buyer->getBuyerID() == inputId)
            {
                return buyer;
            }
            
        }
        return nullptr;
    }

    Seller* Database::findSellerByName(string inputName){
        for (auto &&seller : listSellers)
        {
            if (seller->getBuyerName() == inputName)
            {
                return seller;
            }
            
        }
        return nullptr;
    }

    Item* Database::findItemById(int itemId, Store*& foundInStore) {
    // Loop melalui setiap toko yang ada di database
    for (Store* store : listStores) {
        // Loop melalui setiap item di dalam toko tersebut
        for (Item* item : store->getInventoryItems()) { // Asumsi ada fungsi getListItem() di Store
            if (item->getItemId() == itemId) { // Asumsi ada fungsi getItemId() di Item
                foundInStore = store;
                return item;
            }
        }
    }
    return nullptr;
}

    Transaction* Database::findTransactionById(int transactionId) {
        for (auto &&transaction : transactionHistory) {
            if (transaction.getTransactionId() == transactionId) {
                return &transaction;
            }
        }
        return nullptr;
    }


    void Database::addBuyer(Buyer* buyer) {
        listBuyers.push_back(buyer); // Menambahkan pointer buyer ke akhir vector 'buyers'
    }
    void Database::addSeller(Seller* seller) {
        listSellers.push_back(seller); // Menambahkan pointer buyer ke akhir vector 'buyers'
    }

