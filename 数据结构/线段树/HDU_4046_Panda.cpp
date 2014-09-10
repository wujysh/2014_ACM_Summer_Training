#include <iostream>
#include <algorithm>
#include <string>
#include <cstdio>
using namespace std;

const int MAXN = 50010;
int N, M, a[MAXN], nCase, cnt;
string line;
bool flag;

struct Node {
    int l, r, mid;
    int sum;
} node[MAXN * 4];

void pushup(int rt) {
    node[rt].sum = node[rt << 1].sum + node[(rt << 1) | 1].sum;
}

void build(int l, int r, int rt) {
    node[rt].l = l;
    node[rt].r = r;
    node[rt].mid = (l + r) >> 1;
    if (l == r) {
        node[rt].sum = a[l];
    } else {
        build(l, node[rt].mid, (rt << 1));
        build(node[rt].mid + 1, r, (rt << 1) | 1);
        pushup(rt);
    }
}

void update(int p, int x, int rt) {
    if (node[rt].l == p && p == node[rt].r) {
        node[rt].sum = x;
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

int query(int l, int r, int rt) {
    if (l == node[rt].l && node[rt].r == r) {
        return node[rt].sum;
    } else {
        if (r <= node[rt].mid) {
            return query(l, r, rt << 1);
        } else if (l > node[rt].mid) {
            return query(l, r, (rt << 1) | 1);
        } else {
            return query(l, node[rt].mid, rt << 1) + query(node[rt].mid + 1, r, (rt << 1) | 1);
        }
    }
}

void solve() {
    scanf("%d%d", &N, &M);
    cin >> line;
    if (N <= 2) {
        flag = true;
    } else {
        flag = false;
    }
    for (int i = 0; i <= N - 3; i++) {
        if (line[i] == 'w' && line[i + 1] == 'b' && line[i + 2] == 'w') {
            a[i] = 1;
        } else {
            a[i] = 0;
        }
    }

    if (!flag) build(0, N - 3, 1);

    printf("Case %d:\n", ++cnt);
    for (int i = 0; i < M; i++) {
        int op, a, b;
        char ch;
        scanf("%d", &op);
        if (op == 0) {
            scanf("%d%d", &a, &b);
            if (b + 1 - a <= 2 || flag) {
                printf("0\n");
                continue;
            }
            printf("%d\n", query(a, b - 2, 1));
        } else if (op == 1) {
            scanf("%d %c", &a, &ch);
            line[a] = ch;
            if (a >= 2 && a <= N - 1) {
                if (line[a - 2] == 'w' && line[a - 1] == 'b' && line[a] == 'w') {
                    update(a - 2, 1, 1);
                } else {
                    update(a - 2, 0, 1);
                }
            }
            if (a >= 1 && a <= N - 2) {
                if (line[a - 1] == 'w' && line[a] == 'b' && line[a + 1] == 'w') {
                    update(a - 1, 1, 1);
                } else {
                    update(a - 1, 0, 1);
                }
            }
            if (a >= 0 && a <= N - 3) {
                if (line[a] == 'w' && line[a + 1] == 'b' && line[a + 2] == 'w') {
                    update(a, 1, 1);
                } else {
                    update(a, 0, 1);
                }
            }
        }
    }
}

int main() {
    cnt = 0;
    scanf("%d", &nCase);
    while (nCase--) {
        solve();
    }
    return 0;
}
