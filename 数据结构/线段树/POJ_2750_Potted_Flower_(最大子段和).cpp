#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100010;
int N, M, a[MAXN];

struct Node {
    int l, r, mid;
    int sum, max, maxl, maxr, min, minl, minr;
} node[MAXN * 4];

void pushup(int rt) {
    node[rt].sum = node[rt << 1].sum + node[(rt << 1) | 1].sum;
    node[rt].maxl = max(node[rt << 1].maxl, node[rt << 1].sum + node[(rt << 1) | 1].maxl);
    node[rt].maxr = max(node[(rt << 1) | 1].maxr, node[(rt << 1) | 1].sum + node[rt << 1].maxr);
    node[rt].minl = min(node[rt << 1].minl, node[rt << 1].sum + node[(rt << 1) | 1].minl);
    node[rt].minr = min(node[(rt << 1) | 1].minr, node[(rt << 1) | 1].sum + node[rt << 1].minr);
    node[rt].max = max(max(node[rt << 1].max, node[(rt << 1) | 1].max), node[rt << 1].maxr + node[(rt << 1) | 1].maxl);
    node[rt].min = min(min(node[rt << 1].min, node[(rt << 1) | 1].min), node[rt << 1].minr + node[(rt << 1) | 1].minl);
}

void build(int l, int r, int rt) {
    node[rt].l = l;
    node[rt].r = r;
    node[rt].mid = (l + r) >> 1;
    if (l == r) {
        node[rt].sum = a[l];
        node[rt].max = node[rt].maxl = node[rt].maxr = a[l];
        node[rt].min = node[rt].minl = node[rt].minr = a[l];
    } else {
        build(l, node[rt].mid, (rt << 1));
        build(node[rt].mid+1, r, (rt << 1) | 1);
        pushup(rt);
    }
}

void update(int p, int x, int rt) {
    if (node[rt].l == p && p == node[rt].r) {
        node[rt].sum = x;
        node[rt].max = node[rt].maxl = node[rt].maxr = x;
        node[rt].min = node[rt].minl = node[rt].minr = x;
    } else {
        if (p <= node[rt].mid) {
            update(p, x, (rt << 1));
        }
        if (node[rt].mid < p) {
            update(p, x, (rt << 1) | 1);
        }
        pushup(rt);
    }
}

void solve() {
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
    }

    build(1, N, 1);

    cin >> M;
    for (int i = 0; i < M; i++) {
        int p, x;
        cin >> p >> x;

        update(p, x, 1);
        a[p] = x;

        if (node[1].max == node[1].sum) {
            cout << node[1].sum - node[1].min << endl;
        } else {
            cout << max(node[1].max, node[1].sum - node[1].min) << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> N) {
        solve();
    }
    return 0;
}
