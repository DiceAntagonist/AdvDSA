#include <iostream>
#include <map>
#include <string>
using namespace std;

// Tree Node
class Node {
public:
    map<char, Node*> childrn; // Children of the node
    int start;                // Start index of edge
    int* end;                 // End index of edge

    Node(int s, int* e) : start(s), end(e) {}
};

// Suffix Tree
class SuffixTree {
    string s;                 // Input string
    Node* root;               // Root node
    int* gEnd;                // Global end pointer for all leaf nodes
    int n;                    // Length of input string

    // Build suffix tree
    void addSuffix(int pos) {
        Node* cur = root;
        for (int i = pos; i < n; i++) {
            if (cur->childrn.find(s[i]) == cur->childrn.end()) {
                cur->childrn[s[i]] = new Node(i, gEnd);
            }
            cur = cur->childrn[s[i]];
        }
    }

    // Recursively print the tree
    void print(Node* node, int depth = 0) {
        for (auto& [ch, child] : node->childrn) {
            cout << string(depth * 2, ' ') << "|-- "
                 << s.substr(child->start, *child->end - child->start + 1) << endl;
            print(child, depth + 1);
        }
    }

public:
    SuffixTree(const string& str) : s(str + "$"), n(str.size() + 1) {
        gEnd = new int(-1);
        root = new Node(-1, new int(-1));
        for (int i = 0; i < n; i++) {
            gEnd[0] = i;
            addSuffix(i);
        }
    }

    void show() {
        cout << "Suffix Tree Structure:\n";
        print(root);
    }
};

int main() {
    string input;
    cout << "Enter string: ";
    cin >> input;

    SuffixTree tree(input);
    tree.show();

    return 0;
}
