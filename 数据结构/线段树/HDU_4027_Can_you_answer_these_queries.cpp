#include <iostream>
#include <cstdio>
#include <cmath>
#define LL long long
#define Max(a,b) ((a) > (b) ? (a) : (b))
#define Min(a,b) ((a) < (b) ? (a) : (b))
using namespace std;

const int MAXN = 100010;
struct Node {
    int left, right, mid;
    long long sum;
    bool flag;
} node[MAXN * 4];
int N, M, nCase;

void build(int l, int r, int rt) {
    node[rt].left = l;
    node[rt].right = r;
    node[rt].mid = (l + r) >> 1;
    node[rt].sum = 0;
    node[rt].flag = 1;
    if (l < r) {
        build(l, node[rt].mid, rt << 1);
        build(node[rt].mid + 1, r, (rt << 1) | 1);
    }
}

void insert(int p, LL x, int rt) {
    if (node[rt].left == node[rt].right) {
        if (x == 0 || x == 1) {
            node[rt].flag = 0;
        } else {
            node[rt].flag = 1;
        }
        node[rt].sum = x;
    } else {
        if (p <= node[rt].mid) {
            insert(p, x, rt << 1);
        } else {
            insert(p, x, (rt << 1) | 1);
        }
        node[rt].sum = node[rt << 1].sum + node[(rt << 1) | 1].sum;
        node[rt].flag = node[rt << 1].flag | node[(rt << 1) | 1].flag;
    }
}

void update(int l, int r, int rt) {
    //cout << rt << endl;
    if (node[rt].flag) {
        if (node[rt].left == node[rt].right) {
            node[rt].sum = sqrt(node[rt].sum);
            if(node[rt].sum == 1)  node[rt].flag = 0;
        } else {
            if (r <= node[rt].mid) {
                update(l, r, rt << 1);
            } else if(l > node[rt].mid) {
                update(l, r, (rt << 1) | 1);
            } else {
                update(l, node[rt].mid, rt << 1);
                update(node[rt].mid + 1, r, (rt << 1) | 1);
            }
            node[rt].sum = node[rt << 1].sum + node[(rt << 1) | 1].sum;
            node[rt].flag = node[rt << 1].flag | node[(rt << 1) | 1].flag;
        }
    }
}

LL query(int l, int r, int rt) {
    //cout << rt << endl;
    if (node[rt].left == l && node[rt].right == r) {
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

int main() {
    while (~scanf("%d", &N)) {
        printf("Case #%d:\n", ++nCase);
        build(1, N, 1);
        for (int i = 1; i <= N; i++) {
            long long x;
            scanf("%I64d", &x);
            insert(i, x, 1);
        }
        scanf("%d", &M);
        for (int i = 0; i < M; i++) {
            int op, a, b;
            scanf("%d%d%d", &op, &a, &b);
            int p = Min(a, b), q = Max(a, b);
            if (op == 0) {
                update(p, q, 1);
            } else if (op == 1) {
                printf("%I64d\n", query(p, q, 1));
            }
        }
        printf("\n");
    }
    return 0;
}
