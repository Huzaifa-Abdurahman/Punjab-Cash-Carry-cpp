#ifndef ORDER_H
#define ORDER_H
#include <iostream>
#include <string>
using namespace std;

class Order {
private:
    string productNames[10];
    int quantities[10];
    int itemCount;

public:
    Order() : itemCount(0) {}

    bool addItem(const string& productName, int quantity) {
        if (itemCount < 10) {
            productNames[itemCount] = productName;
            quantities[itemCount] = quantity;
            itemCount++;
            return true;
        } else {
            cout << "Cart full, cannot add more items.\n";
            return false;
        }
    }

    void displayOrder() const {
        if (itemCount == 0) {
            cout << "Order is empty.\n";
            return;
        }
        cout << "Order Details:\n";
        for (int i = 0; i < itemCount; ++i) {
            cout << "- " << productNames[i] << " x " << quantities[i] << endl;
        }
    }

    int getItemCount() const {
        return itemCount;
    }
};
#endif
