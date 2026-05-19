// Design a hash table for a product inventory system where keys are product IDs, and values are stock details. Implement separate chaining and linear probing for collision handling. Analyze time complexity.
  
#include <iostream>
#include <list>
using namespace std;

struct Product {
    int productId;
    int quantity;
    double price;
};

class HashTableChaining {
    int size;
    list<Product>* table;

public:
    HashTableChaining(int s) {
        size = s;
        table = new list<Product>[size];
    }

    int hashFunction(int key) {
        return key % size;
    }

    void insert(Product p) {
        int index = hashFunction(p.productId);
        table[index].push_back(p);
    }

    void search(int id) {
        int index = hashFunction(id);
        for (auto p : table[index]) {
            if (p.productId == id) {
                cout << "Found: ID=" << p.productId
                     << " Qty=" << p.quantity
                     << " Price=" << p.price << endl;
                return;
            }
        }
        cout << "Product not found\n";
    }

    void display() {
        for (int i = 0; i < size; i++) {
            cout << i << " -> ";
            for (auto p : table[i]) {
                cout << "[" << p.productId << "] ";
            }
            cout << endl;
        }
    }
};

class HashTableLinear {
    int size;
    Product* table;
    bool* occupied;

public:
    HashTableLinear(int s) {
        size = s;
        table = new Product[size];
        occupied = new bool[size];

        for (int i = 0; i < size; i++)
            occupied[i] = false;
    }

    int hashFunction(int key) {
        return key % size;
    }

    void insert(Product p) {
        int index = hashFunction(p.productId);

        while (occupied[index]) {
            index = (index + 1) % size;
        }

        table[index] = p;
        occupied[index] = true;
    }

    void search(int id) {
        int index = hashFunction(id);
        int start = index;

        while (occupied[index]) {
            if (table[index].productId == id) {
                cout << "Found: ID=" << table[index].productId
                     << " Qty=" << table[index].quantity
                     << " Price=" << table[index].price << endl;
                return;
            }
            index = (index + 1) % size;
            if (index == start) break;
        }
        cout << "Product not found\n";
    }

    void display() {
        for (int i = 0; i < size; i++) {
            if (occupied[i])
                cout << i << " -> [" << table[i].productId << "]\n";
            else
                cout << i << " -> NULL\n";
        }
    }
};

// ---------- MAIN MENU ----------
int main() {
    int size, choice, method;
    cout << "Enter hash table size: ";
    cin >> size;

    HashTableChaining chain(size);
    HashTableLinear linear(size);

    cout << "\nChoose Collision Handling Method:\n";
    cout << "1. Separate Chaining\n";
    cout << "2. Linear Probing\n";
    cin >> method;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Insert Product\n";
        cout << "2. Search Product\n";
        cout << "3. Display Table\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            Product p;
            cout << "Enter Product ID: ";
            cin >> p.productId;
            cout << "Enter Quantity: ";
            cin >> p.quantity;
            cout << "Enter Price: ";
            cin >> p.price;

            if (method == 1)
                chain.insert(p);
            else
                linear.insert(p);
        }

        else if (choice == 2) {
            int id;
            cout << "Enter Product ID to search: ";
            cin >> id;

            if (method == 1)
                chain.search(id);
            else
                linear.search(id);
        }

        else if (choice == 3) {
            if (method == 1)
                chain.display();
            else
                linear.display();
        }

    } while (choice != 4);

    cout << "Program exited.\n";
    return 0;
}

