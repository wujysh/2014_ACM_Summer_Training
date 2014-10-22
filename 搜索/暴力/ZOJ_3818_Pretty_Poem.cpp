#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

int t;
string s, a, b, c;

bool solve() {
    string tmp = "";
    int l = s.length();
    for (int i = 0; i < l; i++) {
        if ((s[i] >= 'A' && s[i] <= 'Z') || ( s[i] >= 'a' && s[i] <= 'z') || (s[i] == ' ')) {
            tmp += s[i];
        }
    }
    l = tmp.length();
    for (int len = 1; len < l; len++) {
        a = tmp.substr(0, len);
        for (int len2 = 1; 2 * (len + len2) < tmp.length(); len2++) {
            b = tmp.substr(len, len2);
            if (a == b) continue;
            int pos = len + len2;
            if (pos + len < l && tmp.substr(pos, len) == a) {
                pos += len;
                if (pos + len2 < l && tmp.substr(pos, len2) == b) {
                    pos += len2;
                    if (pos + len == l && tmp.substr(pos, len) == a) return true;
                    int pos2 = l - len - len2;
                    if (pos2 > pos && tmp.substr(pos2, len + len2) == a + b) {
                        c = tmp.substr(pos, pos2 - pos);
                        if (c != a && c != b) return true;
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    scanf("%d", &t);
    getchar();
    for (int ca = 1; ca <= t; ca++) {
        getline(cin, s);
        if (solve()) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
