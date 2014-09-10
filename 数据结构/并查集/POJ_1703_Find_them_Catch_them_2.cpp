#include <cstdio>
using namespace std;

const int MAXN = 200010;
int N, M, nCase, father[MAXN], rank[MAXN];

int find_set(int x) {
    return father[x] = father[x] == x ? x : find_set(father[x]);
}

void union_set(int x, int y) {
    int a = find_set(x), b = find_set(y);
    if (rank[a] < rank[b]) {
        father[a] = b;
    } else {
        father[b] = a;
        if (rank[a] == rank[b]) {
            rank[a]++;
        }
    }
}

void init() {
    for (int i = 1; i <= 2*N; i++) {
        father[i] = i;
        rank[i] = 1;
    }
}

void solve() {
    for (int i = 0; i < M; i++) {
        char op;
        int a, b;
        getchar();
        scanf("%c%d%d", &op, &a, &b);
        if (op == 'D') {
            union_set(a, b+N);
            union_set(b, a+N);
        } else if (op == 'A') {
            if (find_set(a) == find_set(b+N)) {
                printf("In different gangs.\n");
            } else if (find_set(a) == find_set(b)) {
                printf("In the same gang.\n");
            } else {
                printf("Not sure yet.\n");
            }
        }
    }
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        scanf("%d%d", &N, &M);
        init();
        solve();
    }
    return 0;
}
