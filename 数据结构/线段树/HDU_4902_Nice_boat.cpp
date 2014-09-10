#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 100010;
struct Node {
    int left, right, mid, max;
    bool flag;
} node[MAXN * 4];
int N, Q, nCase;

void build(int l, int r, int rt) {
    node[rt].left = l;
    node[rt].right = r;
    node[rt].mid = (l + r) >> 1;
    node[rt].max = 0;
    node[rt].flag = 0;
    if (l < r) {
        build(l, node[rt].mid, rt << 1);
        build(node[rt].mid + 1, r, (rt << 1) | 1);
    }
}

void pushdown(int rt) {
    if (node[rt].left == node[rt].right || node[rt].flag == 0) return;
    node[rt << 1].max = node[(rt << 1) | 1].max = node[rt].max;
    node[rt << 1].flag = node[(rt << 1) | 1].flag = node[rt].flag;
    node[rt].flag = 0;
}

void insert(int l, int r, int x, int rt) {
    if (node[rt].left == l && node[rt].right == r) {
        node[rt].max = x;
        node[rt].flag = 1;
    } else {
        pushdown(rt);
        if (r <= node[rt].mid) {
            insert(l, r, x, rt << 1);
        } else if (l > node[rt].mid) {
            insert(l, r, x, (rt << 1) | 1);
        } else {
            insert(l, node[rt].mid, x, rt << 1);
            insert(node[rt].mid + 1, r, x, (rt << 1) | 1);
        }
        node[rt].max = max(node[rt << 1].max, node[(rt << 1) | 1].max);
        if (node[rt << 1].max == node[(rt << 1) | 1].max && node[rt << 1].flag && node[(rt << 1) | 1].flag) {
            node[rt].flag = 1;
        }
    }
}

int gcd(int a, int b) {
    return (b == 0) ? a : gcd(b, a%b);
}

void update(int l, int r, int x, int rt) {
    if (node[rt].flag && node[rt].left == l && node[rt].right == r) {
        if (node[rt].max > x) {
            node[rt].max = gcd(node[rt].max, x);
        }
    } else {
        pushdown(rt);
        if (r <= node[rt].mid) {
            update(l, r, x, rt << 1);
        } else if(l > node[rt].mid) {
            update(l, r, x, (rt << 1) | 1);
        } else {
            update(l, node[rt].mid, x, rt << 1);
            update(node[rt].mid + 1, r, x, (rt << 1) | 1);
        }
        node[rt].max = max(node[rt << 1].max, node[(rt << 1) | 1].max);
        if (node[rt << 1].max == node[(rt << 1) | 1].max && node[rt << 1].flag && node[(rt << 1) | 1].flag) {
            node[rt].flag = 1;
        }
    }
}

void output(int rt) {
    if (node[rt].left == node[rt].right) {
        cout << node[rt].max << " ";
    } else {
        pushdown(rt);
        output(rt << 1);
        output((rt << 1) | 1);
    }
}

void solve() {
    cin >> N;
    build(1, N, 1);
    for (int i = 1; i <= N; i++) {
        int x;
        cin >> x;
        insert(i, i, x, 1);
    }
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int t, l, r, x;
        cin >> t >> l >> r >> x;
        if (t == 1) {
            insert(l, r, x, 1);
        } else if (t == 2) {
            update(l, r, x, 1);
        }
    }
    output(1);
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        solve();
    }
    return 0;
}
