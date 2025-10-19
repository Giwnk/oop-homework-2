#include <iostream>
#include <vector>
#include <string>
#include "../Headers/Seller.h"
#include "../Headers/Store.h"
#include "../Headers/Buyer.h"
using namespace std;

Seller::Seller( string inputName, string inputEmail, string inputAddress, string inputPhoneNum, BankCustomer* inputCustomer, string inputStoreName, Store* inputStore)
        : Buyer(inputPhoneNum, inputName, inputEmail, inputAddress, inputCustomer), sellerId(++sellerIdCounter), storeName(inputStoreName), associatedStore(inputStore) {}

    string Seller::getStoreName(){
        return storeName;
    }
    
    Store* Seller::getAssociatedStore(){
        return associatedStore;
    }


    int Seller::getSellerId(){
        return sellerId;
    }

    void Seller::showInfoSeller() {
        cout << "\n========================" << endl;
        cout << ">>> == SELLER INFO == <<< " << endl;
        cout << "========================\n" << endl;
        cout << "Seller ID: " << getSellerId() << endl;
        cout << "Seller Name: " << getBuyerName() << endl;
        cout << "Seller Email: " << getBuyerEmail() << endl;
        cout << "Seller Phone Number: " << getBuyerPhoneNum() << endl;
        cout << "Seller Address: " << getBuyerAddress() << endl;
        cout << "Store Name: " << getStoreName() << endl;
        getAssociatedStore()->showDetailStore();
    }