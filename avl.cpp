#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int val) {
        key = val;
        left = right = nullptr;
        height = 1;
    }
};

int getHeight(Node* node) {
    if (node == nullptr) return 0;
    return node->height;
}

int getBalance(Node* node) {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}

Node* insert(Node* node, int key) {
    // Standard BST insert
    if (node == nullptr)
        return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // No duplicates

    // Update height
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Balance factor
    int balance = getBalance(node);

    // Balancing cases

    // Left Left
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

int main() {
    Node* root = nullptr;
    int choice, key;

    do {
        cout << "\n--- AVL Tree Operations ---\n";
        cout << "1. Insert\n";
        cout << "2. Inorder Traversal\n";
        cout << "3. Print Height\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                root = insert(root, key);
                break;
            case 2:
                cout << "Inorder Traversal: ";
                inorder(root);
                cout << endl;
                break;
            case 3:
                cout << "Height of AVL Tree: " << getHeight(root) << endl;
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
