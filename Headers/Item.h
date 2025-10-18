#if !defined(ITEM)
#define ITEM
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Item{
    private:
    inline static int itemIdCounter = 000;
    int itemId, itemQuantity;
    string itemName;
    double itemPrice;

    public:
    Item(string inputItemName, double inputItemPrice, int inputItemQuantity);

    int getItemId();
    int getItemQuantity();
    string getItemName();
    double getItemPrice();

    void setItemName(string inputNewItemName);
    void setItemPrice(int inputNewItemPrice);
    void addItemQuantity(int inputNewItemQuantity);
    bool reduceQuantity(int inputAmount);
    void showDetailItem();
};

#endif // ITEM
