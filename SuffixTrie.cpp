#include <iostream>
#include <list>
#define MAX_CHAR 256
using namespace std;

class SuffixTrieNode {
private:
    SuffixTrieNode* children[MAX_CHAR];
    list<int>* indexes;

public:
    SuffixTrieNode() {
        indexes = new list<int>;
        for (int i = 0; i < MAX_CHAR; i++)
            children[i] = NULL;
    }
    void insertSuffix(string suffix, int index);
    list<int>* search(string pat);
};

class SuffixTrie {
private:
    SuffixTrieNode root;

public:
    SuffixTrie(string txt) {
        for (int i = 0; i < txt.length(); i++)
            root.insertSuffix(txt.substr(i), i);
    }
    void search(string pat);
};

void SuffixTrieNode::insertSuffix(string s, int index) {
    indexes->push_back(index);
    if (s.length() > 0) {
        char cIndex = s.at(0);
        if (children[cIndex] == NULL)
            children[cIndex] = new SuffixTrieNode();
        children[cIndex]->insertSuffix(s.substr(1), index + 1);
    }
}

list<int>* SuffixTrieNode::search(string s) {
    if (s.length() == 0)
        return indexes;
    if (children[s.at(0)] != NULL)
        return (children[s.at(0)])->search(s.substr(1));
    else
        return NULL;
}

void SuffixTrie::search(string pat) {
    list<int>* result = root.search(pat);
    if (result == NULL)
        cout << "Pattern not found" << endl;
    else {
        list<int>::iterator i;
        int patLen = pat.length();
        for (i = result->begin(); i != result->end(); ++i)
            cout << "Pattern found at position " << *i - patLen << endl;
    }
}

int main() {
    string txt, pat;
    cout << "Enter the text (no spaces): ";
    cin >> txt;
    SuffixTrie S(txt);
    cout << "Enter the pattern to search (no spaces): ";
    cin >> pat;
    S.search(pat);
    return 0;
}
