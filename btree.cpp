#include <iostream>
using namespace std;

class BTreeNode {
    int *keys;
    int t;
    BTreeNode **C;
    int n;
    bool leaf;

public:
    BTreeNode(int t, bool leaf);
    void traverse();
    BTreeNode* search(int k);
    void insertNonFull(int k);
    void splitChild(int i, BTreeNode* y);

    friend class BTree;
};

class BTree {
    BTreeNode* root;
    int t;

public:
    BTree(int t);
    void traverse();
    BTreeNode* search(int k);
    void insert(int k);
};

BTreeNode::BTreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;
    keys = new int[2 * t - 1];
    C = new BTreeNode*[2 * t];
    n = 0;
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf)
            C[i]->traverse();
        cout << " " << keys[i];
    }
    if (!leaf)
        C[i]->traverse();
}

BTreeNode* BTreeNode::search(int k) {
    int i = 0;
    while (i < n && k > keys[i])
        i++;
    if (i < n && keys[i] == k)
        return this;
    if (leaf)
        return nullptr;
    return C[i]->search(k);
}

void BTreeNode::insertNonFull(int k) {
    int i = n - 1;
    if (leaf) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        n++;
    } else {
        while (i >= 0 && keys[i] > k)
            i--;
        if (C[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, C[i + 1]);
            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (!y->leaf) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];
    n++;
}

BTree::BTree(int t1) {
    root = nullptr;
    t = t1;
}

void BTree::traverse() {
    if (root != nullptr)
        root->traverse();
}

BTreeNode* BTree::search(int k) {
    if (root == nullptr)
        return nullptr;
    else
        return root->search(k);
}

void BTree::insert(int k) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);
            root = s;
        } else {
            root->insertNonFull(k);
        }
    }
}

int main() {
    int t;
    cout << "Enter the minimum degree of the B-Tree: ";
    cin >> t;

    BTree btree(t);

    int choice, key;
    do {
        cout << "\n1. Insert\n2. Traverse\n3. Search\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                btree.insert(key);
                break;
            case 2:
                cout << "Traversal of the B-Tree: ";
                btree.traverse();
                cout << endl;
                break;
            case 3:
                cout << "Enter key to search: ";
                cin >> key;
                cout << (btree.search(key) ? "Key Found" : "Key Not Found") << endl;
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 4);

    return 0;
}
