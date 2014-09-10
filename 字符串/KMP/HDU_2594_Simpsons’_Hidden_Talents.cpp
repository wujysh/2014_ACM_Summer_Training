#include <iostream>
#include <cstring>
#include <string>
using namespace std;

const int MAXN = 100010;
string s1, s2, str;
int next[MAXN];

void getNext(string pattern) {
    memset(next, 0, sizeof(next));
    for (int i = 1; i < pattern.length(); i++) {
        int j = i;
        while (j > 0) {
            j = next[j];
            if (pattern[j] == pattern[i]) {
                next[i+1] = j + 1;
                break;
            }
        }
    }
}

void output() {
    if (next[str.length()]) {
        cout << str.substr(0, next[str.length()]) << " " << next[str.length()] << endl;
    } else {
        cout << 0 << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> s1) {
        cin >> s2;
        str = s1 + "|" + s2;
        getNext(str);
        output();
    }
    return 0;
}
