/*
    Name: Lydia Frame
    Date: July 12, 2025
    Project: Array-Based Hash Table with Linear Probing (No STL)
*/

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Circle structure
struct Circle {
    double radius;
    string color;

    void display() const {
        cout << "Radius: " << radius << ", Color: " << color << endl;
    }
};

// Node structure
struct Node {
    string* key = nullptr;
    Circle* data = nullptr;
};

// Hash Function
int MyHasher(const string& key, int tableSize) {
    int sum = 0;
    for (char ch : key)
        sum += ch;
    return sum % tableSize;
}

// Utility: Check if number is prime
bool isPrime(int num) {
    if (num < 2) return false;
    for (int i = 2; i <= sqrt(num); ++i)
        if (num % i == 0) return false;
    return true;
}

// Utility: Find next prime number
int nextPrime(int num) {
    while (!isPrime(num)) ++num;
    return num;
}

// Insert function with linear probing
bool InsertElement(Node* table, int size, const string& key, Circle* circle) {
    int index = MyHasher(key, size);
    int start = index;
    do {
        if (table[index].key == nullptr) {
            table[index].key = new string(key);
            table[index].data = circle;
            return true;
        }
        index = (index + 1) % size;
    } while (index != start);

    return false; // Table full
}

// Display element using linear probing
bool DisplayElement(Node* table, int size, const string& key) {
    int index = MyHasher(key, size);
    int start = index;

    do {
        if (table[index].key == nullptr) return false;
        if (*table[index].key == key) {
            cout << "Element found at index " << index << ":\n";
            table[index].data->display();
            return true;
        }
        index = (index + 1) % size;
    } while (index != start);

    return false;
}

// Destroy current hash table
void DestroyTable(Node*& table, int& size) {
    if (table == nullptr) return;

    for (int i = 0; i < size; ++i) {
        delete table[i].key;
        delete table[i].data;
    }
    delete[] table;
    table = nullptr;
    size = 0;
}

int main() {
    Node* hashTable = nullptr;
    int tableSize = 0;
    int choice;
    string key;
    int numElements;

    do {
        cout << "\n--- Hash Table Menu ---\n";
        cout << "1. Create New Hash Table\n";
        cout << "2. Insert Circle\n";
        cout << "3. Display Circle\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            DestroyTable(hashTable, tableSize);
            cout << "Enter number of elements to store: ";
            cin >> numElements;
            tableSize = nextPrime(numElements * 2);
            hashTable = new Node[tableSize];
            cout << "Created hash table of size " << tableSize << ".\n";
            break;

        case 2:
            if (!hashTable) {
                cout << "Please create the hash table first.\n";
                break;
            }
            cout << "Enter key (lowercase letters only): ";
            cin >> key;
            {
                Circle* newCircle = new Circle();
                cout << "Enter radius: ";
                cin >> newCircle->radius;
                cout << "Enter color: ";
                cin >> newCircle->color;

                if (InsertElement(hashTable, tableSize, key, newCircle)) {
                    cout << "Circle inserted.\n";
                } else {
                    cout << "Hash table is full. Cannot insert.\n";
                    delete newCircle;
                }
            }
            break;

        case 3:
            if (!hashTable) {
                cout << "Please create the hash table first.\n";
                break;
            }
            cout << "Enter key to display: ";
            cin >> key;
            if (!DisplayElement(hashTable, tableSize, key)) {
                cout << "Element not found.\n";
            }
            break;

        case 4:
            DestroyTable(hashTable, tableSize);
            cout << "Exiting and cleaning up memory...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
