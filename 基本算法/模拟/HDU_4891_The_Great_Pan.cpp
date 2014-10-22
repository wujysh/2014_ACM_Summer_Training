#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

string str;
int n;
long long ans;

bool getSplit() {
    int len = str.size();
    bool flag = false;
    long long cnt = 1;
    for (int i = 0; i < len; i++) {
        if (flag) {
            if (str[i] == '}') {
                ans *= cnt;
                if (ans > 1e5) return false;
                flag = false;
                cnt = 1;
            } else if (str[i] == '|') {
                cnt++;
                if (cnt > 1e5) return false;
            }
        } else if (str[i] == '{') {
            flag = true;
        }
    }
    return true;
}

bool getDollar() {
    int len = str.size();
    bool flag = false;
    long long cnt = 1;
    int i = 0;
    while (i < len) {
        if (!flag && str[i] == '$') {
            flag = true;
            i++;
        }
        if (flag) {
            if (str[i] == ' ') {
                cnt = 0;
                while (i < len && str[i] == ' ') {
                    i++;
                    cnt++;
                }
                ans *= (cnt + 1);
                if (ans > 1e5) return false;
            }
        }
        if (flag && str[i] == '$') flag = false;
        i++;
    }
    return true;
}

int main() {
    while (~scanf("%d", &n)) {
        getchar();
        str.clear();
        ans = 1;
        for (int i = 0; i < n; i++) {
            string st;
            getline(cin, st);
            str += st;
        }
        if (getSplit() && getDollar()) {
            cout << ans << endl;
        } else {
            cout << "doge" << endl;
        }
    }
    return 0;
}
