#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100010;
int a[MAXN], aa[MAXN], n, d, ans, all;

struct Node {
    int left, right, mid, value;
} node[MAXN * 4];

void build(int l, int r, int rt) {
    node[rt].left = l;
    node[rt].right = r;
    node[rt].mid = (l + r) >> 1;
    node[rt].value = 0;
    if (l < r) {
        build(l, node[rt].mid, rt << 1);
        build(node[rt].mid + 1, r, (rt << 1) | 1);
    }
}

void update(int p, int x, int rt) {
    if (node[rt].left == node[rt].right) {
        node[rt].value = x;
    } else {
        if (p <= node[rt].mid) {
            update(p, x, rt << 1);
        } else {
            update(p, x, (rt << 1) | 1);
        }
        node[rt].value = max(node[rt << 1].value, node[(rt << 1) | 1].value);
    }
}

int query(int l, int r, int rt) {
    if (l <= node[rt].left && node[rt].right <= r) {
        return node[rt].value;
    } else {
        int ret = 0;
        if (l <= node[rt].mid) {
            ret = max(ret, query(l, r, rt << 1));
        }
        if (r > node[rt].mid) {
            ret = max(ret, query(l, r, (rt << 1) | 1));
        }
        return ret;
    }
}

void init() {
    ans = 1;
}

void input() {
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        aa[i] = a[i];
    }
    sort(aa, aa+n);
    all = unique(aa, aa+n) - aa;
    build(0, all-1, 1);
}

void work() {
    for (int i = 0; i < n; i++) {
        int j = query(lower_bound(aa, aa+all, a[i]-d) - aa, upper_bound(aa, aa+all, a[i]+d) - aa - 1, 1);
        update(lower_bound(aa, aa+all, a[i]) - aa, j+1, 1);
        ans = max(ans, j+1);
    }
}

void output() {
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> d) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
