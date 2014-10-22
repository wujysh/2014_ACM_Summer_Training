#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 30010;
int n, m, father[MAXN], rank_set[MAXN], num_set[MAXN];

int find_set(int x) {
    return father[x] == x ? x : father[x] = find_set(father[x]);
}

void union_set(int x, int y) {
    int a = find_set(x), b = find_set(y);
    if (a == b) return;
    if (rank_set[a] < rank_set[b]) {
        father[a] = b;
        num_set[b] += num_set[a];
    } else {
        father[b] = a;
        num_set[a] += num_set[b];
        if (rank_set[a] == rank_set[b]) {
            rank_set[a]++;
        }
    }
}

void init() {
    for (int i = 0; i < n; i++) {
        father[i] = i;
        rank_set[i] = 1;
        num_set[i] = 1;
    }
}

void solve() {
    for (int i = 0; i < m; i++) {
        int k, x, y;
        scanf("%d", &k);
        scanf("%d", &x);
        for (int j = 1; j < k; j++) {
            scanf("%d", &y);
            union_set(x, y);
            x = y;
        }
    }
    printf("%d\n", num_set[find_set(0)]);
}

int main() {
    while (~scanf("%d%d", &n, &m) && (n || m)) {
        init();
        solve();
    }
    return 0;
}
