#include <iostream>
#include <string>
#include <vector>
#include "../Headers/Item.h"
using namespace std;


Item::Item(string inputItemName, double inputItemPrice, int inputItemQuantity){
        itemId = ++itemIdCounter;
        itemName = inputItemName;
        itemPrice = inputItemPrice;
        itemQuantity = inputItemQuantity;
    }

    int Item::getItemId(){return itemId;}
    int Item::getItemQuantity(){return itemQuantity;}
    string Item::getItemName(){return itemName;}
    double Item::getItemPrice(){return itemPrice;}

    void Item::setItemName(string inputNewItemName){
        itemName = inputNewItemName;
    }
    void Item::setItemPrice(int inputNewItemPrice){
        if (inputNewItemPrice >= 0)
        {
            itemPrice = inputNewItemPrice;
        }
        
    }
    void Item::addItemQuantity(int inputNewItemQuantity){
        if (inputNewItemQuantity > 0)
        {
            itemQuantity += inputNewItemQuantity;
        }
    }

    bool Item::reduceQuantity(int inputAmount){
        if (inputAmount > 0 && inputAmount <= itemQuantity)
        {
            itemQuantity -= inputAmount;
            return true;
        } else{
            return false;
        }
    }

    void Item::showDetailItem(){
        cout << "Item ID: " << getItemId() << endl;
        cout << "Item Name: " << getItemName() << endl;
        cout << "Item Price: " << getItemPrice() << endl;
        cout << "Item Quantity: " << getItemQuantity() << endl;
    }