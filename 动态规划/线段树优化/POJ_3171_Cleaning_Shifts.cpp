#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 10010;
const int MAXM = 86400;
const long long INF = 0x3f3f3f3f3f3f3f3f;
int N, M, E, minl, maxr;
long long ans;

struct Cow {
    int T1, T2, S;
    Cow() {}
    Cow(int _T1, int _T2, int _S) : T1(_T1), T2(_T2), S(_S) {}
    bool operator<(const Cow &b) const {
        return T2 < b.T2;
    }
} cow[MAXN];

struct Node {
    int left, right, mid;
    long long value;
} node[MAXM * 4];

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
    E++;
    ans = 0;
    build(M, E, 1);
    minl = MAXN;
    maxr = 0;
}

void input() {
    for (int i = 0; i < N; i++) {
        cin >> cow[i].T1 >> cow[i].T2 >> cow[i].S;
        cow[i].T2++;
        minl = min(minl, cow[i].T1);
        maxr = max(maxr, cow[i].T2);
    }
}

void work() {
    if (minl > M || maxr < E) {
        ans = -1;
        return;
    }

    sort(cow, cow+N);

    update(M, 0, 1);
    for (int i = 0; i < N; i++) {
        if (cow[i].T1 == M) {
            update(cow[i].T2, cow[i].S, 1);
        } else {
            long long tmp = query(cow[i].T1, cow[i].T2, 1);
            update(cow[i].T2, tmp + cow[i].S, 1);
        }
    }
    ans = query(E, E, 1);

    //for (int i = 0; i < 10; i++) {
    //    cout << node[i].left << " " << node[i].right << " " << node[i].value << endl;
    //}
}

void output() {
    if (ans == INF) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> N >> M >> E) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
