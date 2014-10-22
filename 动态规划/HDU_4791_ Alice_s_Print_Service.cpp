#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 100010;
int n, m, nCase;

struct Query {
    int index;
    long long q, p;
    Query() {}
    Query(int _index, long long _q) : index(_index), q(_q) {}
} query[MAXN];

struct Node {
    long long s, p, price;
    Node() {}
    Node(long long _s, long long _p) : s(_s), p(_p) {}
} node[MAXN];

void input() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%I64d%I64d", &node[i].s, &node[i].p);
    }
    for (int i = 0; i < m; i++) {
        scanf("%I64d", &query[i].q);
        query[i].index = i;
    }
}

bool cmp(Query a, Query b) {
    return a.q < b.q;
}

bool cmp2(Query a, Query b) {
    return a.index < b.index;
}

void solve() {
    node[n-1].price = node[n-1].s * node[n-1].p;
    for (int i = n-2; i >= 0; i--) {
        node[i].price = min(node[i+1].price, node[i].s * node[i].p);
    }

    sort(query, query+m, cmp);

    int pre = 0;
    for (int i = 0; i < m; i++) {
        while (node[pre].s <= query[i].q && pre < n) {
            pre++;
        }
        if (pre == n) {
            query[i].p = query[i].q * node[n-1].p;
        } else {
            query[i].p = min(query[i].q * node[pre-1].p, node[pre].price);
        }
    }

    sort(query, query+m, cmp2);

    for (int i = 0; i < m; i++) {
        printf("%I64d\n", query[i].p);
    }
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        input();
        solve();
    }
    return 0;
}
