#if !defined(SELLER)
#define SELLER

#include <iostream>
#include <string>
#include <vector>
#include "Buyer.h"
#include "Store.h"


using namespace std;


class Seller : public Buyer{
private:
    inline static int sellerIdCounter = 200;
    int sellerId;
    string storeName;
    vector<Item> listedItems;
    Store* associatedStore;
public:
    // Constructor for Seller, calling Buyer's constructor
    Seller(string inputPhoneNum, string inputName, string inputStoreName, string inputEmail, string inputAddress, BankCustomer* inputCustomer, Store* inputStore);

    string getStoreName();
    Store* getAssociatedStore();
    int getSellerId();
    void showInfoSeller();

};

#endif // SELLER
