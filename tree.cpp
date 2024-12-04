#include <iostream>
using namespace std;

class Node {
public:
    int value;
    Node* left;
    Node* right;

    Node(int val) {
        value = val;
        left = nullptr;
        right = nullptr;
    }
};

class Tree {
    Node* root;

    Node* insertNode(Node* current, int value) {
        if (current == nullptr)
            return new Node(value);

        if (value < current->value)
            current->left = insertNode(current->left, value);
        else if (value > current->value)
            current->right = insertNode(current->right, value);

        return current;
    }

    bool searchNode(Node* current, int value) {
        if (current == nullptr)
            return false;

        if (current->value == value)
            return true;

        if (value < current->value)
            return searchNode(current->left, value);
        return searchNode(current->right, value);
    }

    void inOrderTraversal(Node* current) {
        if (current == nullptr)
            return;

        inOrderTraversal(current->left);
        cout << current->value << " ";
        inOrderTraversal(current->right);
    }

public:
    Tree() {
        root = nullptr;
    }

    void insert(int value) {
        root = insertNode(root, value);
    }

    bool search(int value) {
        return searchNode(root, value);
    }

    void traverse() {
        inOrderTraversal(root);
    }
};

int main() {
    Tree tree;
    int choice, value;

    do {
        cout << "\n1. Insert\n2. Search\n3. Traverse\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insert(value);
                break;
            case 2:
                cout << "Enter value to search: ";
                cin >> value;
                if (tree.search(value))
                    cout << "Value found in the tree.";
                else
                    cout << "Value not found in the tree.";
                break;
            case 3:
                cout << "Tree (in-order traversal): ";
                tree.traverse();
                cout << endl;
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
