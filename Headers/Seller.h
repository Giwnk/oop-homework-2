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
    Store* associatedStore;
    vector<Item> listedItems;
    public:
    // Constructor for Seller, calling Buyer's constructor
    Seller( string inputName, string inputEmail, string inputAddress,string inputPhoneNum, BankCustomer* inputCustomer,string inputStoreName, Store* inputStore);

    string getStoreName();
    Store* getAssociatedStore();
    int getSellerId();
    void showInfoSeller();

};

#endif // SELLER
