#include <iostream>
#include <cstring>
#include <string>
using namespace std;

const int MAXN = 100010;
string s1, s2, str;
int next[MAXN], ans, n, T;

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

void init() {
    ans = 0;
}

void input() {
    cin >> n;
    cin >> str;
}

void work() {
    getNext(str);
    for (int i = 0; i <= str.length(); i++) {
        cout << next[i] << " ";
        if (next[i]) {
            ans += 2;
        }
    }
}

void output() {
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        init();
        input();
        work();
        output();
    }

    return 0;
}
