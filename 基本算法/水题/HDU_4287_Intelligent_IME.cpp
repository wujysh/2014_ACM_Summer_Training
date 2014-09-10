#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <map>
using namespace std;

vector<int> a;
map<int, int> b;
int n, m, nCase;

void init() {
    a.clear();
    b.clear();
}

void solve() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        a.push_back(x);
    }
    for (int i = 0; i < m; i++) {
        char str[10];
        scanf("%s", str);
        int sum = 0;
        for (int j = 0; j < strlen(str); j++) {
            if (str[j] >= 'a' && str[j] <= 'c') {
                sum = sum * 10 + 2;
            }
            if (str[j] >= 'd' && str[j] <= 'f') {
                sum = sum * 10 + 3;
            }
            if (str[j] >= 'g' && str[j] <= 'i') {
                sum = sum * 10 + 4;
            }
            if (str[j] >= 'j' && str[j] <= 'l') {
                sum = sum * 10 + 5;
            }
            if (str[j] >= 'm' && str[j] <= 'o') {
                sum = sum * 10 + 6;
            }
            if (str[j] >= 'p' && str[j] <= 's') {
                sum = sum * 10 + 7;
            }
            if (str[j] >= 't' && str[j] <= 'v') {
                sum = sum * 10 + 8;
            }
            if (str[j] >= 'w' && str[j] <= 'z') {
                sum = sum * 10 + 9;
            }
        }
        b[sum] = b[sum] + 1;
    }
}

void output() {
    for (int i = 0; i < n; i++) {
        printf("%d\n", b[a[i]]);
    }
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        init();
        solve();
        output();
    }
    return 0;
}
