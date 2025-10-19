#include <iostream>
#include <vector>
#include <string>
#include "Database.h"

using namespace std;

    vector<Buyer*> Database::listBuyers;

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
    void Database::addStore(Store* store) {
        listStores.push_back(store); // Menambahkan pointer buyer ke akhir vector 'buyers'
    }
    void Database::addBankCustomer(BankCustomer* customer) {
        mainBank.addBankCustomer(*customer); // Menambahkan pointer buyer ke akhir vector 'buyers'
    }

    void Database::addSeller(Seller* seller) {
        listSellers.push_back(seller); // Menambahkan pointer buyer ke akhir vector 'buyers'
    }

    void Database::seedData(){
        // === BANK CUSTOMERS ===
    BankCustomer* customerBudi = new BankCustomer("Budi Santoso", 5000000);
    BankCustomer* customerCitra = new BankCustomer("Citra Lestari", 7500000);
    BankCustomer* customerAgus = new BankCustomer("Agus Wijoyo", 10000000);
    BankCustomer* customerDiana = new BankCustomer("Diana Putri", 1200000);
    BankCustomer* customerEko = new BankCustomer("Eko Prasetyo", 25000000);
    addBankCustomer(customerBudi);
    addBankCustomer(customerCitra);
    addBankCustomer(customerAgus);
    addBankCustomer(customerDiana);
    addBankCustomer(customerEko);

    // === BUYERS ===
    Buyer* buyerBudi = new Buyer("Budi Santoso", "budi@email.com", "Jl. Merdeka 1", "081234567890", customerBudi);
    Buyer* buyerCitra = new Buyer("Citra Lestari", "citra@email.com", "Jl. Sudirman 2", "081112223333", customerCitra);
    Buyer* buyerDiana = new Buyer("Diana Putri", "diana@email.com", "Jl. Mawar 3", "081555666777", customerDiana);
    addBuyer(buyerBudi);
    addBuyer(buyerCitra);
    addBuyer(buyerDiana);

    // === SELLER 1 & STORE 1 (Toko Kopi) ===
    Store* storeKopiJaya = new Store("Kopi Jaya");
    Seller* sellerAgus = new Seller("Agus Wijoyo", "agus@kopi.com", "Jl. Kopi 10", "085566778899", customerAgus, "Kopi Jaya", storeKopiJaya);
    storeKopiJaya->setAssociatedSeller(sellerAgus);
    addStore(storeKopiJaya);
    addSeller(sellerAgus);

    // --- Item untuk Toko Kopi Jaya ---
    Item* itemKopiR = new Item("Kopi Robusta", 50000, 100);
    Item* itemKopiA = new Item("Kopi Arabika", 75000, 80);
    Item* itemGulaA = new Item("Gula Aren Cair", 25000, 200);
    storeKopiJaya->addItem(itemKopiR);
    storeKopiJaya->addItem(itemKopiA);
    storeKopiJaya->addItem(itemGulaA);

    // === SELLER 2 & STORE 2 (Toko ATK) ===
    Store* storeATKSukses = new Store("ATK Sukses");
    Seller* sellerEko = new Seller("Eko Prasetyo", "eko@atk.com", "Jl. Pendidikan 20", "087711112222", customerEko, "ATK Sukses", storeATKSukses);
    storeATKSukses->setAssociatedSeller(sellerEko);
    addStore(storeATKSukses);
    addSeller(sellerEko);

    // --- Item untuk Toko ATK Sukses ---
    Item* itemBuku = new Item("Buku Tulis Sinar Dunia", 5000, 500);
    Item* itemPena = new Item("Pena Gel Pilot G2", 15000, 300);
    Item* itemMap = new Item("Map Plastik", 2000, 1000);
    storeATKSukses->addItem(itemBuku);
    storeATKSukses->addItem(itemPena);
    storeATKSukses->addItem(itemMap);
    
    // === RIWAYAT TRANSAKSI ===
    // Budi membeli 2 Kopi Robusta dari Agus
    transactionHistory.emplace_back(100000.0, 2, itemKopiR->getItemId(), buyerBudi->getBuyerID(), sellerAgus->getSellerId(), "Kopi Robusta", "Budi Santoso");
    
    // Citra membeli 1 Kopi Arabika dari Agus
    transactionHistory.emplace_back(75000.0, 1, itemKopiA->getItemId(), buyerCitra->getBuyerID(), sellerAgus->getSellerId(), "Kopi Arabika", "Citra Lestari");
    
    // Budi membeli 3 Gula Aren dari Agus (Budi jadi pelanggan setia)
    transactionHistory.emplace_back(75000.0, 3, itemGulaA->getItemId(), buyerBudi->getBuyerID(), sellerAgus->getSellerId(), "Gula Aren Cair", "Budi Santoso");
    
    // Diana membeli 10 Buku Tulis dari Eko
    transactionHistory.emplace_back(50000.0, 10, itemBuku->getItemId(), buyerDiana->getBuyerID(), sellerEko->getSellerId(), "Buku Tulis Sinar Dunia", "Diana Putri");
    
    // Citra membeli 5 Pena Gel dari Eko
    transactionHistory.emplace_back(75000.0, 5, itemPena->getItemId(), buyerCitra->getBuyerID(), sellerEko->getSellerId(), "Pena Gel Pilot G2", "Citra Lestari");

    // Budi membeli Kopi Robusta lagi (Item terlaris)
    transactionHistory.emplace_back(50000.0, 1, itemKopiR->getItemId(), buyerBudi->getBuyerID(), sellerAgus->getSellerId(), "Kopi Robusta", "Budi Santoso");
    }
