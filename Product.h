#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
using namespace std;
class Product {
private:
    string name;
    string category;
    double price;
    int quantity;
    string supplier;

public:
    Product() : name(""), category(""), price(0.0), quantity(0), supplier("") {}

    Product(string n, string c, double p, int q, string s)
        : name(n), category(c), price(p), quantity(q), supplier(s) {}
    void setpname(string n){
    	name=n;
	}
	void setcategory(string c){
		category=c;
	}
	void setprice(double p){
		price=p;
	}

	void setsupplier(string s){
		supplier=s;
	}
    string getName() const { return name; }
    string getCategory() const { return category; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    string getSupplier() const { return supplier; }

    void setQuantity(int q) { quantity = q; }

    void display() const {
        cout << "Name: " << name
             << ", Category: " << category
             << ", Price: " << price
             << ", Quantity: " << quantity
             << ", Supplier: " << supplier << endl;
    }
};
#endif
