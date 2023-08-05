#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Item {
public:
    string name;
    double price;
    int quantity;

    Item() : name(""), price(0.0), quantity(0) {}
    Item(string n, double p, int q) : name(n), price(p), quantity(q) {}

    void display() const {
        cout << name << " | Price:Rs." << price << " | Quantity: " << quantity << endl;
    }
};

class ShoppingCart {
public:
    vector<Item> items;

    void addItem(const Item& item) {
        items.push_back(item);
    }

    void display() const {
        cout << "\n===== Shopping Cart =====" << endl;
        for (const auto& item : items) {
            item.display();
        }
        cout << "Total cost: $" << getTotalCost() << endl;
    }

    double getTotalCost() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item.price * item.quantity;
        }
        return total;
    }
};

class Inventory {
public:
    vector<Item> items;

    void addItem(const Item& item) {
        items.push_back(item);
    }

    void display() const {
        cout << "\n===== Inventory =====" << endl;
        for (const auto& item : items) {
            item.display();
        }
    }

    void decreaseItemQuantity(const string& itemName, int quantityToDecrease) {
        for (auto& item : items) {
            if (item.name == itemName) {
                item.quantity = max(0, item.quantity - quantityToDecrease);
                break;
            }
        }
    }
};

void saveCart(const ShoppingCart& cart, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& item : cart.items) {
            outFile << item.name << " " << item.price << " " << item.quantity << endl;
        }
        outFile.close();
        cout << "Shopping cart saved to " << filename << endl;
    }
    else {
        cout << "Error: Unable to save shopping cart to file!" << endl;
    }
}

void loadCart(ShoppingCart& cart, const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string itemName;
        double price;
        int quantity;
        while (inFile >> itemName >> price >> quantity) {
            cart.addItem(Item(itemName, price, quantity));
        }
        inFile.close();
        cout << "Shopping cart loaded from " << filename << endl;
    }
    else {
        cout << "No saved shopping cart found." << endl;
    }
}

void saveInventory(const Inventory& inventory, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& item : inventory.items) {
            outFile << item.name << " " << item.price << " " << item.quantity << endl;
        }
        outFile.close();
        cout << "Inventory saved to " << filename << endl;
    }
    else {
        cout << "Error: Unable to save inventory to file!" << endl;
    }
}

void loadInventory(Inventory& inventory, const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string itemName;
        double price;
        int quantity;
        while (inFile >> itemName >> price >> quantity) {
            inventory.addItem(Item(itemName, price, quantity));
        }
        inFile.close();
        cout << "Inventory loaded from " << filename << endl;
    }
    else {
        cout << "No saved inventory found." << endl;
    }
}

void displayMenu() {
    cout << "\n===== Shopping Menu =====" << endl;
    cout << "1. View Inventory" << endl;
    cout << "2. Add Item to Cart" << endl;
    cout << "3. View Shopping Cart" << endl;
    cout << "4. Checkout" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Inventory inventory;
    ShoppingCart cart;

    // Load inventory and shopping cart from files (if available)
    loadInventory(inventory, "inventory.txt");
    loadCart(cart, "shopping_cart.txt");
    
    int choice;
    string itemName;
    double price;
    int quantity;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            inventory.display();
            break;

        case 2:
            cout << "\nEnter Item Name: ";
            cin.ignore();
            getline(cin, itemName);
            cout << "Enter Price: ";
            cin >> price;
            cout << "Enter Quantity: ";
            cin >> quantity;
            cart.addItem(Item(itemName, price, quantity));
            cout << itemName << " added to the shopping cart!" << endl;
            break;

        case 3:
            cart.display();
            break;

        case 4:
            cout << "\n===== Checkout =====" << endl;
            cout << "Total Cost: $" << cart.getTotalCost() << endl;
            saveCart(cart, "shopping_cart.txt");
            for (const auto& item : cart.items) {
                inventory.decreaseItemQuantity(item.name, item.quantity);
            }
            saveInventory(inventory, "inventory.txt");
            cout << "Checkout complete! Thank you for shopping with us." << endl;
            return 0;

        case 5:
            saveCart(cart, "shopping_cart.txt");
            saveInventory(inventory, "inventory.txt");
            cout << "\nThank you for using our shopping service. Goodbye!" << endl;
            return 0;

        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
