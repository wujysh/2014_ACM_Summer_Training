#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 10010;
int n, m;
long long dpmin[MAXN], dpmax[MAXN];
vector<int> child[MAXN];
bool flag;

void init() {
    for (int i = 0; i < MAXN; i++) {
        child[i].clear();
        dpmin[i] = 1;
        dpmax[i] = -1;
    }
    flag = true;
}

void input() {
    int x, w;
    char op;
    for (int i = 2; i <= n; i++) {
        scanf("%d", &x);
        child[x].push_back(i);
        child[i].push_back(x);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %c %d", &x, &op, &w);
        if (op == '=') {
            dpmin[x] = dpmax[x] = w;
        }
        if (op == '<') {
            dpmax[x] = w-1;
        }
        if (op == '>') {
            dpmin[x] = w+1;
        }
    }
}

void DP(int x, int father) {
    if (!flag) return;
    if (dpmax[x] != -1 && dpmin[x] > dpmax[x]) {
        flag = false;
        return;
    }
    long long Min = 0;
    for (int i = 0; i < child[x].size(); i++) {
        int c = child[x][i];
        if (c != father) {
            DP(c, x);
            Min += dpmin[c];
        }
    }
    dpmin[x] = max(dpmin[x], Min+1);
    if (dpmax[x] != -1 && dpmin[x] > dpmax[x]) {
        flag = false;
        return;
    }
}

void solve() {
    DP(1, 0);
    if (flag) {
        printf("True\n");
    } else {
        printf("Lie\n");
    }
}

int main() {
    while (~scanf("%d", &n)) {
        init();
        input();
        solve();
    }
    return 0;
}
