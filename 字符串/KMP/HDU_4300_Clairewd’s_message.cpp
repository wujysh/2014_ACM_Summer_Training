#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

const int MAXN = 100010;
const int INF = 0x3f3f3f3f;
int T, n, next[MAXN], ans;
string S, text;

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
    ans = INF;
}

void input() {
    cin >> S;
    cin >> text;
}

void work() {
    for (int i = text.length() / 2; i < text.length(); i++) {
        string temp = text;
        for (int j = i; j < text.length(); j++) {
            temp[j] = S[temp[j] - 'a'];
        }
        cout << text << " " << temp << endl;
        getNext(temp);
        for (int j = 1; j <= temp.length(); j++) {
            cout << next[j] << " ";
        }
        cout << endl;
        if (temp.length() - next[temp.length()])
        ans = min(ans, i - ((int)temp.length() - next[temp.length()]));
    }
}

void output() {
    cout << ans << endl;
    for (int i = 0; i < ans; i++) {
        cout << text[i];
    }
    for (int i = 0; i < ans; i++) {
        cout << S[text[i] - 'a'];
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        input();
        work();
        output();
    }
    return 0;
}
