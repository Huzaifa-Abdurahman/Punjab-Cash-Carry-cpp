//Developers Huzaifa Abdurahman & Ali Ahmed
//Roll no   241113             & 241109
//version 1.0
// University Air
#include<iostream>
#include<string>
#include<fstream>
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
Customer cus[50];
int cusCount = 0;

Inventory inv;

Order sales[100];
int totalSales = 0;

void loadproductfile() {
inv.loadFromFile();
}

int cusbyemail(const string& email) {
    for (int i = 0; i < cusCount; ++i) {
        if (cus[i].matchEmail(email)) return i;
    }
    return -1;
}

void cusSignup() {
    if (cusCount >= 50) {
        cout << "Customer limit reached.\n";
        return;
    }
    string name, email, address;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter email: ";
    cin >> email;
    if (cusbyemail(email) != -1) {
        cout << "Customer with this email already exists.\n";
        return;
    }
    cout << "Enter address: ";
    cin.ignore();
    getline(cin, address);

    cus[cusCount++] = Customer(name, email, address);
    cout << "Signup successful.\n";
}

void cusLogin() {
    string email;
    cout << "Enter your email: ";
    cin >> email;

    int index = cusbyemail(email);
    if (index == -1) {
        cout << "Customer not found.\n";
        return;
    }

    Customer& current = cus[index];
    Order cart;

    int choice;
    do {
        cout << "\n--- Customer Order Menu ---\n";
        cout << "1. View Products\n";
        cout << "2. Add Product to Cart\n";
        cout << "3. Show Cart\n";
        cout << "4. Place Order\n";
        cout << "5. View Order History\n";
        cout << "6. Exit to Customer Menu\n";
        cout << "Enter choice: ";
        cin >> choice;
if (choice == 1) {
    inv.displayInventory();
}
      
         else if (choice == 2) {
            string pname;
            int qty;
            cout << "Enter product name: ";
            cin >> pname;
            cout << "Enter quantity: ";
            cin >> qty;
            cart.addItem(pname, qty);
        } else if (choice == 3) {
            cart.displayOrder();
        } else if (choice == 4) {
            current.addOrder(cart);
            if (totalSales < 100) sales[totalSales++] = cart;
            cout << "Order placed successfully.\n";
            cart = Order(); 
        } else if (choice == 5) {
            current.viewOrderHistory();
        }
    } while (choice != 6);
}

void staffLogin() {
    string staffPass = "admin123";
    string input;
    cout << "Enter staff password: ";
    cin >> input;

    if (input != staffPass) {
        cout << "Invalid password.\n";
        return;
    }

    int choice;
    do {
        cout << "\n--- Staff Management Menu ---\n";
        cout << "1. Add Product\n";
        cout << "2. Remove Product\n";
        cout << "3. View Customers\n";
        cout << "4. View Sales Report\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string name, category, supplier;
            double price;
            int quantity;

            cout << "Enter product name: ";
            cin >> name;
            cout << "Enter category: ";
            cin >> category;
            cout << "Enter price: ";
            cin >> price;
            cout << "Enter quantity: ";
            cin >> quantity;
            cout << "Enter supplier: ";
            cin >> supplier;

            Product p(name, category, price, quantity, supplier);
            inv.addProduct(p);
            cout << "Product added.\n";
        } else if (choice == 2) {
            string name;
            cout << "Enter product name to remove: ";
            cin >> name;
            inv. removeProduct(name);
        } else if (choice == 3) {
            for (int i = 0; i < cusCount; ++i) {
                cus[i].display();
            }
        } else if (choice == 4) {
            cout << "\n--- Sales Report ---\n";
            for (int i = 0; i < totalSales; ++i) {
                cout << "Sale #" << (i + 1) << ":\n";
                sales[i].displayOrder();
            }
        }
    } while (choice != 5);
}

int main() {
    loadproductfile();

    int choice;
    do {
        cout << "\n------------Main Menu---------------\n";
        cout << "1. Customer Menu\n";
        cout << "2. Staff Menu\n";
        cout << "3. View product Inventory\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int ch;
            do {
                cout << "\n-- Customer Menu --\n";
                cout << "1. Login\n";
                cout << "2. Signup\n";
                cout << "3. Exit to main Menu\n";
                cout << "Enter choice: ";
                cin >> ch;

                if (ch == 1) cusLogin();
                else if (ch == 2) cusSignup();
            } while (ch != 3);
        } else if (choice == 2) {
            staffLogin();
        } else if (choice == 3) {
            inv.displayInventory();
        }

    } while (choice != 4);

    cout << "Exiting Progrm.\n";
    return 0;
}


