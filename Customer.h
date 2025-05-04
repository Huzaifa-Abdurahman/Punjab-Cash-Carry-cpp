#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include <string>
#include"Order.h"
using namespace std;

class Customer {
private:
    string name;
    string email;
    string address;
    Order orderHistory[10]; 
    int orderCount;

public:
    Customer() : name(""), email(""), address(""), orderCount(0) {}

    Customer(string n, string e, string a)
        : name(n), email(e), address(a), orderCount(0) {}

    ~Customer() {}
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getAddress() const { return address; }
    void setName(const string& n) { name = n; }
    void setEmail(const string& e) { email = e; }
    void setAddress(const string& a) { address = a; }

    bool matchEmail(const string& e) const {
        return email == e;
    }

    void display() const {
        cout << "Name: " << name << ", Email: " << email
             << ", Address: " << address << endl;
    }
    bool addOrder(const Order& o) {
        if (orderCount < 10) {
            orderHistory[orderCount++] = o;
            return true;
        } else {
            cout << "Order history full.\n";
            return false;
        }
    }

    void viewOrderHistory() const {
        if (orderCount == 0) {
            cout << "No previous orders.\n";
            return;
        }
        for (int i = 0; i < orderCount; ++i) {
            cout << "Order #" << (i + 1) << ":\n";
            orderHistory[i].displayOrder();
            cout << endl;
        }
    }

    int getOrderCount() const {
        return orderCount;
    }
};
#endif
