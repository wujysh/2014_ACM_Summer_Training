#include <iostream>
#include <cstdio>
#include <map>
using namespace std;

int w, nCase, n;
map<int, int> m;

void init() {
    m.clear();
}

void input() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &w);
        int s = 10000 - (100 - w) * (100 - w);
        m[s]++;
    }
}

void solve() {
    map<int, int>::iterator it=m.begin();
    int a = m.begin()->second;
    bool flag = true;
    int max = a;
    for (it++; it != m.end(); it++) {
        if (it->second != a) {
            flag = false;
        }
        if (it->second > max) {
            max = it->second;
        }
    }
    if (!flag || m.size() == 1) {
        int cnt = 0;
        for (it=m.begin(); it != m.end(); it++) {
            if (it->second == max) {
                if (cnt++) printf(" ");
                printf("%d", it->first);
            }
        }
        printf("\n");
    } else {
        printf("Bad Mushroom\n");
    }
}

int main() {
    scanf("%d", &nCase);
    for (int co = 1; co <= nCase; co++) {
        init();
        input();
        printf("Case #%d:\n", co);
        solve();
    }
    return 0;
}
