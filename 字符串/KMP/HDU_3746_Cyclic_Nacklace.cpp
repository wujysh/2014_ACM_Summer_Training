#include <iostream>
#include <cstring>
#include <string>
using namespace std;

const int MAXN = 100010;
int T, n, l, next[MAXN];
string str;

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

void work() {
    getNext(str);
    n = str.length();
    l = n - next[n];
}

void output() {
    if (n % l == 0 && l != n) {
        cout << 0 << endl;
    } else {
        cout << l - n % l << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> str;
        work();
        output();
    }
    return 0;
}
