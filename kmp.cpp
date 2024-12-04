#include <iostream>
#include <vector>
using namespace std;

vector<int> failure(const string pattern) {
    int m = pattern.length();
    vector<int> f(m, 0);
    int j = 0;

    for (int i = 1; i < m; i++) {
        if (pattern[i] == pattern[j]) {
            j++;
            f[i] = j;
        } else {
            if (j > 0) {
                j = f[j - 1];
                i--; 
            } else {
                f[i] = 0;
            }
        }
    }

    return f;
}

void KMPsearch(const string text, const string pattern) {
    int n = text.length();
    int m = pattern.length();
    vector<int> f = failure(pattern);

    int i = 0, j = 0;

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) {
            cout << "Pattern found at index " << i - j << endl;
            j = f[j - 1];
        } else if (i < n && text[i] != pattern[j]) {
            if (j > 0) {
                j = f[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    string text, pattern;

    cout << "Enter the text: ";
    cin >> text;

    cout << "Enter the pattern: ";
    cin >> pattern;

    KMPsearch(text, pattern);

    return 0;
}
