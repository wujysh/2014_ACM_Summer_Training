#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 50010;
int N, Q, cnt, num[MAXN], b[11][10];

struct Node {
    int l, r, mid;
    int add[55];
} node[MAXN << 2];

void build(int l, int r, int rt) {
    node[rt].l = l;
    node[rt].r = r;
    node[rt].mid = (l + r) >> 1;
    memset(node[rt].add, 0, sizeof(node[rt].add));
    if (l != r) {
        build(l, node[rt].mid, rt << 1);
        build(node[rt].mid+1, r, (rt << 1) | 1);
    }
}

void pushdown(int rt) {
    if (node[rt].l == node[rt].r) return;
    for (int i = 0; i < 55; i++) {
        node[rt << 1].add[i] += node[rt].add[i];
        node[(rt << 1) | 1].add[i] += node[rt].add[i];
        node[rt].add[i] = 0;
    }
}

void update(int l, int r, int x, int i, int j, int rt) {
    if (l == node[rt].l && node[rt].r == r) {
        node[rt].add[b[i][j]] += x;
    } else {
        pushdown(rt);
        if (r <= node[rt].mid) {
            update(l, r, x, i, j, rt << 1);
        } else if (l > node[rt].mid) {
            update(l, r, x, i, j, (rt << 1) | 1);
        } else {
            update(l, node[rt].mid, x, i, j, rt << 1);
            update(node[rt].mid+1, r, x, i, j, (rt << 1) | 1);
        }
    }
}

int query(int p, int rt) {
    if (p == node[rt].l && p == node[rt].r) {
        int ret = 0;
        for (int i = 1; i <= 10; i++) {
            ret += node[rt].add[b[i][p % i]];
        }
        return ret;
    } else {
        pushdown(rt);
        if (p <= node[rt].mid) {
            return query(p, rt << 1);
        }
        if (p > node[rt].mid) {
            return query(p, (rt << 1) | 1);
        }
    }
}

void init() {
    cnt = 0;
    for (int i = 1; i <= 10; i++) {
        for (int j = 0; j < i; j++) {
            b[i][j] = cnt++;
        }
    }
}

void solve() {
    for (int i = 1; i <= N; i++) {
        scanf("%d", &num[i]);
    }

    build(1, N, 1);

    int op, a, b, k, c;
    scanf("%d", &Q);
    while (Q--) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d%d%d", &a, &b, &k, &c);
            update(a, b, c, k, a%k, 1);
        } else if (op == 2) {
            scanf("%d", &a);
            printf("%d\n", num[a] + query(a, 1));
        }
    }
}

int main() {
    init();
    while (~scanf("%d", &N)) {
        solve();
    }
    return 0;
}
