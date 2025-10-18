#include <iostream>
#include <vector>
#include <string>
#include "../Headers/Seller.h"
#include "../Headers/Store.h"
#include "../Headers/Buyer.h"
using namespace std;

Seller::Seller(string inputPhoneNum, string inputName, string inputStoreName, string inputEmail, string inputAddress, BankCustomer* inputCustomer, Store* inputStore)
        : Buyer(inputPhoneNum, inputName, inputEmail, inputAddress, inputCustomer), sellerId(++sellerIdCounter), associatedStore(inputStore), storeName(inputStoreName) {}

    string Seller::getStoreName(){
        return storeName;
    }
    
    Store* Seller::getAssociatedStore(){
        return associatedStore;
    }

    void Seller::showInfoSeller() {
        cout << "\n========================" << endl;
        cout << ">>> == SELLER INFO == <<< " << endl;
        cout << "========================\n" << endl;
        cout << "Seller ID: " << getBuyerID() << endl;
        cout << "Seller Name: " << getBuyerName() << endl;
        cout << "Seller Email: " << getBuyerEmail() << endl;
        cout << "Seller Phone Number: " << getBuyerPhoneNum() << endl;
        cout << "Seller Address: " << getBuyerAddress() << endl;
        cout << "Store Name: " << getStoreName() << endl;
        getAssociatedStore()->showDetailStore();
    }