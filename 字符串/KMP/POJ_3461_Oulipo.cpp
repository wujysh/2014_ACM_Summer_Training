#include <iostream>
#include <string>
#include <vector>
using namespace std;

string W, T;
int nCase;

vector<int> find_substring(string pattern, string text) {
    int n = pattern.size();
    vector<int> next(n+1, 0);
    for (int i = 1; i < n; i++) {
        int j = i;
        while (j > 0) {
            j = next[j];
            if (pattern[j] == pattern[i]) {
                next[i+1] = j + 1;
                break;
            }
        }
    }
    vector<int> positions;
    int m = text.size();
    for (int i = 0, j = 0; i < m; i++) {
        if (j < n && text[i] == pattern[j]) {
            j++;
        } else {
            while (j > 0) {
                j = next[j];
                if (text[i] == pattern[j]) {
                    j++;
                    break;
                }
            }
        }
        if (j == n) {
            positions.push_back(i - n + 1);
        }
    }
    return positions;
}

void input() {
    getline(cin, W);
    getline(cin, T);
}

void output() {
    cout << find_substring(W, T).size() << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    cin.ignore();
    while (nCase--) {
        input();
        output();
    }
    return 0;
}
