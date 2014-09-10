//#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

const int MAXN = 50010;
const int MAXM = 500010;
const int INF = 0x3f3f3f3f;
int n, m, ans;

struct Node {
    int left, right, mid, value;
} node[MAXN * 4];

struct Sorter {
    int left, right;
} sorter[MAXM];

void build(int l, int r, int rt) {
    node[rt].left = l;
    node[rt].right = r;
    node[rt].mid = (l + r) >> 1;
    node[rt].value = INF;
    if (l < r) {
        build(l, node[rt].mid, rt << 1);
        build(node[rt].mid + 1, r, (rt << 1) | 1);
    }
}

void update(int p, int x, int rt) {
    if (node[rt].left == node[rt].right) {
        node[rt].value = min(node[rt].value, x);
    } else {
        if (p <= node[rt].mid) {
            update(p, x, rt << 1);
        } else {
            update(p, x, (rt << 1) | 1);
        }
        node[rt].value = min(node[rt << 1].value, node[(rt << 1) | 1].value);
    }
}

int query(int l, int r, int rt) {
    if (l <= node[rt].left && node[rt].right <= r) {
        return node[rt].value;
    } else {
        int ret = INF;
        if (l <= node[rt].mid) {
            ret = min(ret, query(l, r, rt << 1));
        }
        if (node[rt].mid < r) {
            ret = min(ret, query(l, r, (rt << 1) | 1));
        }
        return ret;
    }
}

void init() {
    build(1, n, 1);
}

void input() {
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &sorter[i].left, &sorter[i].right);
        //cin >> sorter[i].left >> sorter[i].right;
    }
}

void work() {
    for (int i = 0; i < m; i++) {
        if (sorter[i].left == 1) {
            update(sorter[i].right, 1, 1);
        } else {
            if (sorter[i].left < sorter[i].right) {
                int tmp = query(sorter[i].left, sorter[i].right - 1, 1);
                update(sorter[i].right, tmp + 1, 1);
            }
        }
    }
    ans = query(n, n, 1);
}

void output() {
    printf("%d\n", ans);
    //cout << ans << endl;
}

int main() {
    //ios::sync_with_stdio(false);
    while (scanf("%d%d", &n, &m) == 2) {
    //while (cin >> n >> m) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
