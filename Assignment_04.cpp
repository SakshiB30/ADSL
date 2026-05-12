// Construct an expression tree from the given prefix expression, for example, +a^bc-defgh. Then, traverse the tree
// using post- order traversal (non-recursive), and finally, delete the entire tree. Analyze time complexity.

#include <iostream>
#include <stack>
using namespace std;


struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char val) {
        data = val;
        left = right = NULL;
    }
};


bool isOperator(char c) {
    return (c=='+' || c=='-' || c=='*' || c=='/' || c=='^');
}


Node* constructTree(string prefix) {
    stack<Node*> st;

    for (int i = prefix.length()-1; i >= 0; i--) {
        char ch = prefix[i];
        Node* node = new Node(ch);

        if (isOperator(ch)) {
            if (st.size() < 2) {
                cout << "Invalid expression!\n";
                return NULL;
            }
            node->left = st.top(); st.pop();
            node->right = st.top(); st.pop();
        }
        st.push(node);
    }

    return st.top();
}


void postorder(Node* root) {
    if (!root) {
        cout << "Tree is empty!\n";
        return;
    }

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* curr = s1.top();
        s1.pop();
        s2.push(curr);

        if (curr->left) s1.push(curr->left);
        if (curr->right) s1.push(curr->right);
    }

    cout << "Postorder: ";
    while (!s2.empty()) {
        cout << s2.top()->data;
        s2.pop();
    }
    cout << endl;
}


void deleteTree(Node*& root) {
    if (!root) return;

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
    root = NULL;
}


int main() {
    Node* root = NULL;
    string prefix;
    int choice;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Construct Expression Tree (Prefix)\n";
        cout << "2. Postorder Traversal (Non-Recursive)\n";
        cout << "3. Delete Tree\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "Enter prefix expression: ";
            cin >> prefix;

            root = constructTree(prefix);
            if (root)
                cout << "Tree constructed successfully!\n";
            break;

        case 2:
            postorder(root);
            break;

        case 3:
            deleteTree(root);
            cout << "Tree deleted successfully!\n";
            break;

        case 4:
            cout << "Program exited.\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}



