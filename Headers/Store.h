#if !defined(STORE)
#define STORE
#include <iostream>
#include <string>
#include <vector>
#include "Item.h"
using namespace std;

class Seller;

class Store{
    private:
    int inline static storeIdCounter; 
    int storeId;
    string storeName;
    vector<Item*> inventoryItems;
    Seller* associatedSeller;

    public:
    Store(string inputStoreName);

    string getStoreName();
    int getStoreId();
    int getAmountItem();
    Item* searchItemById(int inputItemId);
    vector<Item*> getInventoryItems();
    void setAssociatedSeller(Seller* inputAssociatedSeller);
    Seller* getAssociatedSeller();

    void addItem(Item* inputItem);

    void showDetailStore();

    void showInventory();


};





#endif // STORE
