#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
    int value;
    vector<Node*> children; // General tree allows multiple children

    Node(int val) {
        value = val;
    }
};

class Tree {
    Node* root;

    Node* insertNode(Node* current, int parentValue, int value) {
        if (current == nullptr) {
            return nullptr;
        }

        // If the parent is found, add the new node as its child
        if (current->value == parentValue) {
            Node* newNode = new Node(value);
            current->children.push_back(newNode);
            return current;
        }

        // Recursively check in all children
        for (Node* child : current->children) {
            Node* result = insertNode(child, parentValue, value);
            if (result != nullptr) {
                return result;
            }
        }

        return nullptr;
    }

    bool searchNode(Node* current, int value) {
        if (current == nullptr) {
            return false;
        }

        if (current->value == value) {
            return true;
        }

        // Recursively search in all children
        for (Node* child : current->children) {
            if (searchNode(child, value)) {
                return true;
            }
        }

        return false;
    }

    void traverseNode(Node* current) {
        if (current == nullptr) {
            return;
        }

        cout << current->value << " "; // Visit the current node

        // Traverse all children
        for (Node* child : current->children) {
            traverseNode(child);
        }
    }

public:
    Tree() {
        root = nullptr;
    }

    void insert(int parentValue, int value) {
        if (root == nullptr) {
            // If the tree is empty, create the root node
            root = new Node(parentValue);
            if (parentValue != value) {
                root->children.push_back(new Node(value));
            }
        } else {
            insertNode(root, parentValue, value);
        }
    }

    bool search(int value) {
        return searchNode(root, value);
    }

    void traverse() {
        traverseNode(root);
        cout << endl;
    }
};

int main() {
    Tree tree;
    int choice, parentValue, value;

    do {
        cout << "\n1. Insert\n2. Search\n3. Traverse\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter parent value (or root value if tree is empty): ";
                cin >> parentValue;
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insert(parentValue, value);
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
                cout << "Tree (traversal): ";
                tree.traverse();
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
