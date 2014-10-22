#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 50010;
int n, m, father[MAXN], rank_set[MAXN], ans, cnt;

int find_set(int x) {
    return father[x] = father[x] == x ? x : find_set(father[x]);
}

void union_set(int x, int y) {
    int a = find_set(x), b = find_set(y);
    if (a == b) return;
    if (rank_set[a] < rank_set[b]) {
        father[a] = b;
    } else {
        father[b] = a;
        if (rank_set[a] == rank_set[b]) {
            rank_set[a]++;
        }
    }
}

void init() {
    for (int i = 1; i <= n; i++) {
        father[i] = i;
        rank_set[i] = 1;
    }
    ans = n;
}

void solve() {
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        if (find_set(a) != find_set(b)) {
            ans--;
            union_set(a, b);
        }
    }
    printf("Case %d: %d\n", ++cnt, ans);
}

int main() {
    while (~scanf("%d%d", &n, &m) && (n || m)) {
        init();
        solve();
    }
    return 0;
}
