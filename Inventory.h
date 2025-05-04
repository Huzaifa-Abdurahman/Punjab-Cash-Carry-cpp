// Inventory.h
#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <fstream>
#include "Product.h"
using namespace std;

class Inventory {
private:
    Product pro[100];
    int procount;

public:
    Inventory() : procount(0) {}

    void addProduct(const Product& p) {
        if (procount < 100) {
            pro[procount++] = p;
            savefile();
        }
    }

    void displayInventory() const {
        for (int i = 0; i < procount; ++i) {
            pro[i].display();
        }
    }

    void removeProduct(const string& name) {
        for (int i = 0; i < procount; ++i) {
            if (pro[i].getName() == name) {
                for (int j = i; j < procount - 1; ++j) {
                    pro[j] = pro[j + 1];
                }
                --procount;
                savefile();
                cout << "Product removed.\n";
                return;
            }
        }
        cout << "Product not found.\n";
    }

    void loadFromFile() {
        ifstream file("data.txt");
        if (!file) {
            cout << "Error: data.txt not found\n";
            return;
        }

        string name, category, supplier;
        double price;
        int quantity;

        while (file >> name >> category >> price >> quantity >> supplier) {
            Product p(name, category, price, quantity, supplier);
            addProduct(p);
        }

        file.close();
    }
    
    void savefile() {
        ofstream file("data.txt");
        for (int i = 0; i < procount; ++i) {
            file << pro[i].getName() << " "
                 << pro[i].getCategory() << " "
                 << pro[i].getPrice() << " "
                 << pro[i].getQuantity() << " "
                 << pro[i].getSupplier() << endl;
        }
        file.close();
    }
    void addWithoutSaving(const Product& p) {
        if (procount < 100) {
            pro[procount++] = p;
        }
    }
};

#endif
