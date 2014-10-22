#include <iostream>
#include <cstring>
#include <string>
using namespace std;

const int MAXN = 1000010;
int T, n, l, Next[MAXN];
string str;

void getNext(string pattern) {
    memset(Next, 0, sizeof(Next));
    for (int i = 1; i < pattern.length(); i++) {
        int j = i;
        while (j > 0) {
            j = Next[j];
            if (pattern[j] == pattern[i]) {
                Next[i+1] = j + 1;
                break;
            }
        }
    }
}

void solve() {
    getNext(str);
    n = str.length();
    l = n - Next[n];
    if (n % l == 0) {
        cout << n / l << endl;
    } else {
        cout << 1 << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    while (getline(cin, str) && str.find(".") == string::npos) {
        solve();
    }
    return 0;
}
