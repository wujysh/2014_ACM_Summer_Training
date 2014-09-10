//#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 10010;
const long long INF = 0x3f3f3f3f3f3f3f3f;
int x[MAXN], xx[MAXN], N, S, E, L1, L2, L3, C1, C2, C3, all;
long long ans;

struct Node {
    int left, right, mid;
    long long value;
} node[MAXN * 4];

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

void update(int p, long long x, int rt) {
    //if (rt == 1) cout << "update: " << p << " " << x << endl;
    if (node[rt].left == node[rt].right) {
        node[rt].value = min(x, node[rt].value);
    } else {
        if (p <= node[rt].mid) {
            update(p, x, rt << 1);
        } else {
            update(p, x, (rt << 1) | 1);
        }
        node[rt].value = min(node[rt << 1].value, node[(rt << 1) | 1].value);
    }
}

long long query(int l, int r, int rt) {
    //if (rt == 1) cout << "query: " << l << " " << r << endl;
    if (l <= node[rt].left && node[rt].right <= r) {
        return node[rt].value;
    } else {
        long long ret = INF;
        if (l <= node[rt].mid) {
            ret = min(ret, query(l, r, rt << 1));
        }
        if (r > node[rt].mid) {
            ret = min(ret, query(l, r, (rt << 1) | 1));
        }
        return ret;
    }
}

void init() {
    memset(x, 0, sizeof(x));
}

void input() {
    //cin >> N;
    scanf("%d", &N);
    //cin >> S >> E;
    scanf("%d%d", &S, &E);
    if (S > E) swap(S, E);
    for (int i = 2; i <= N; i++) {
        //cin >> x[i];
        scanf("%d", &x[i]);
        xx[i-1] = x[i];
    }
}

void work() {
    sort(xx, xx+N);
    all = unique(xx, xx+N) - xx;
    int SS = lower_bound(xx, xx+all, x[S]) - xx;
    int EE = upper_bound(xx, xx+all, x[E])-1 - xx;
    build(SS, EE, 1);

    for (int i = SS; i <= EE; i++) {
        if (i == SS) {
            update(i, 0, 1);
        } else {
            long long tmp1 = query(lower_bound(xx, xx+all, xx[i]-L3) - xx, upper_bound(xx, xx+all, xx[i]-1)-1 - xx, 1) + C3;
            long long tmp2 = query(lower_bound(xx, xx+all, xx[i]-L2) - xx, upper_bound(xx, xx+all, xx[i]-1)-1 - xx, 1) + C2;
            long long tmp3 = query(lower_bound(xx, xx+all, xx[i]-L1) - xx, upper_bound(xx, xx+all, xx[i]-1)-1 - xx, 1) + C1;
            update(i, min(tmp1, min(tmp2, tmp3)), 1);
        }
    }
    ans = query(EE, EE, 1);
}

void output() {
    printf("%d\n", ans);
    //cout << ans << endl;
}

int main() {
    //ios::sync_with_stdio(false);
    //while (cin >> L1 >> L2 >> L3 >> C1 >> C2 >> C3) {
    while (scanf("%d%d%d%d%d%d", &L1, &L2, &L3, &C1, &C2, &C3) == 6) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
