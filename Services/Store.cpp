#include <iostream>
#include <vector>
#include <string>
#include "../Headers/Item.h"
#include "../Headers/Store.h"
using namespace std;

Store::Store(string inputStoreName){
        storeId = ++storeIdCounter;
        storeName = inputStoreName;
    
    }

    string Store::getStoreName(){return storeName;}
    int Store::getStoreId(){return storeId;}
    int Store::getAmountItem(){
        int amountItem = inventoryItems.size();
        return amountItem;
    }

    Item* Store::searchItemById(int inputItemId){
        for (auto &&item : inventoryItems)
        {
            if (item->getItemId() == inputItemId)
            {
                return item;
            }
        }
        return nullptr;
    }

    vector<Item*> Store::getInventoryItems(){
        return inventoryItems;
    }

    void Store::setAssociatedSeller(Seller* inputAssociatedSeller){
        associatedSeller = inputAssociatedSeller;
    }

    Seller* Store::getAssociatedSeller(){
        return associatedSeller;
    }

    void Store::addItem(Item *inputItem){
        inventoryItems.push_back(inputItem);
    }

    void Store::showDetailStore(){
        cout << "Store Name: " << storeName << endl;
        cout << "Store ID: " << storeId << endl;
        cout << "Amount Item: " << getAmountItem() << endl;
    }

    void Store::showInventory(){
        for (auto &&item : inventoryItems)
        {
            cout << "ID Item: " << item->getItemId() << endl;
            cout << "Item Name: " << item->getItemName() << endl;
            cout << "Item Price: " << item->getItemPrice() << endl;
            cout << "Item Quantity: " << item->getItemQuantity() << endl;
            cout << "--------------------------" << endl;
        }
    }