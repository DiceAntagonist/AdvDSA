#include <iostream>
#include <vector>
using namespace std;

#define MAX_CHAR 256

class SuffixTrieNode {
public:
    SuffixTrieNode* children[MAX_CHAR] = {nullptr};
    vector<int> indexes;

    void insertSuffix(const string& suffix, int index) {
        indexes.push_back(index);  // Store the starting index of this suffix
        if (!suffix.empty()) {
            char c = suffix[0];  // First character of the suffix
            if (children[c] == nullptr) {
                children[c] = new SuffixTrieNode();
            }
            children[c]->insertSuffix(suffix.substr(1), index + 1);  // Insert the remaining suffix
        }
    }

    vector<int> search(const string& pattern) {
        if (pattern.empty()) return indexes;  // If pattern is empty, return all indexes
        char c = pattern[0];  
        if (children[c] != nullptr) {
            return children[c]->search(pattern.substr(1));  // Search recursively in the child node
        }
        return {};  
    }
};

class SuffixTrie {
    SuffixTrieNode* root;

public:
    SuffixTrie(const string& text) {
        root = new SuffixTrieNode();
        for (int i = 0; i < text.length(); ++i) {
            root->insertSuffix(text.substr(i), i);  // Insert all suffixes starting at index `i`
        }
    }

    vector<int> search(const string& pattern) {
        return root->search(pattern);  // Start searching from the root node
    }
};

int main() {
    string text, pattern;
    cout << "Enter the text: ";
    cin >> text;

    SuffixTrie trie(text);

    cout << "Enter the pattern to search ";
    cin >> pattern;

    vector<int> result = trie.search(pattern);

    if (!result.empty()) {
        cout << "Pattern found at indexes: ";
        for (int index : result) {
            cout << index - pattern.length() + 1 << " ";  // Adjust index to match pattern start
        }
        cout << endl;
    } else {
        cout << "Pattern not found" << endl;
    }

    return 0;
}
