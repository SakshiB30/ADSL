// A book consists of chapters, chapters consist of sections and sections consist of subsections. Construct a tree and print the nodes. Find the time and space requirements of your method.

#include <iostream>
#include <vector>
using namespace std;

struct Node {
    string name;
    vector<Node*> children;

    Node(string n) {
        name = n;
    }
};

 
Node* findNode(Node* root, string target) {
    if (root == NULL) return NULL;
    if (root->name == target) return root;

    for (auto child : root->children) {
        Node* res = findNode(child, target);
        if (res != NULL) return res;
    }
    return NULL;
}


void printTree(Node* root, int level = 0) {
    if (root == NULL) return;

    for (int i = 0; i < level; i++)
        cout << "  ";

    cout << root->name << endl;

    for (auto child : root->children) {
        printTree(child, level + 1);
    }
}


int main() {
    Node* book = new Node("Book");

    int choice;
    string parentName, childName;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Add Chapter\n";
        cout << "2. Add Section\n";
        cout << "3. Add Subsection\n";
        cout << "4. Display Book Structure\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1: {
            cout << "Enter Chapter name: ";
            cin.ignore();
            getline(cin, childName);

            Node* chapter = new Node(childName);
            book->children.push_back(chapter);
            break;
        }

        case 2: {
            cout << "Enter Chapter name to add section: ";
            cin.ignore();
            getline(cin, parentName);

            Node* parent = findNode(book, parentName);

            if (parent) {
                cout << "Enter Section name: ";
                getline(cin, childName);

                Node* section = new Node(childName);
                parent->children.push_back(section);
            } else {
                cout << "Chapter not found!\n";
            }
            break;
        }

        case 3: {
            cout << "Enter Section name to add subsection: ";
            cin.ignore();
            getline(cin, parentName);

            Node* parent = findNode(book, parentName);

            if (parent) {
                cout << "Enter Subsection name: ";
                getline(cin, childName);

                Node* subsection = new Node(childName);
                parent->children.push_back(subsection);
            } else {
                cout << "Section not found!\n";
            }
            break;
        }

        case 4:
            cout << "\nBook Structure:\n";
            printTree(book);
            break;
        }

    } while (choice != 5);

    cout << "Program exited.\n";
    return 0;
}