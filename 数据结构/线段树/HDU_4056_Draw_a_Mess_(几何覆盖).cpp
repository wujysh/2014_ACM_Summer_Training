#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 50010;
int ans[10], n, m, q;

struct Geometry {
    int type;  // 0-Circle, 1-Diamond, 2-Rectangle, 3-Triangle
    int xc, yc, r, c, w, l;
} geometry[MAXN];

struct Node {
    int l, r, mid;
    int num;
} node[MAXN * 4];

void build(int l, int r, int rt) {
    node[rt].l = l;
    node[rt].r = r;
    node[rt].mid = (l + r) >> 1;
    node[rt].num = r - l + 1;
    if (l < r) {
        build(l, node[rt].mid, rt << 1);
        build(node[rt].mid + 1, r, (rt << 1) | 1);
    }
}

void insert(int l, int r, int rt) {
    if (node[rt].num == 0) {
        return;
    }
    if (node[rt].l == l && r == node[rt].r) {
        node[rt].num = 0;
    } else {
        if (r <= node[rt].mid) {
            insert(l, r, rt << 1);
        } else if (node[rt].mid < l) {
            insert(l, r, (rt << 1) | 1);
        } else {
            insert(l, node[rt].mid, rt << 1);
            insert(node[rt].mid + 1, r, (rt << 1) | 1);
        }
        node[rt].num = node[rt << 1].num + node[(rt << 1) | 1].num;
    }
}

int query(int l, int r, int rt) {
    if (node[rt].num == 0) {
        return 0;
    }
    if (l == node[rt].l && node[rt].r == r) {
        return node[rt].num;
    } else {
        if (r <= node[rt].mid) {
            return query(l, r, rt << 1);
        } else if (node[rt].mid < l) {
            return query(l, r, (rt << 1) | 1);
        } else {
            return query(l, node[rt].mid, rt << 1) + query(node[rt].mid + 1, r, (rt << 1) | 1);
        }
    }
}

void input() {
    char name[10];
    for (int i = 0; i < q; i++) {
        scanf("%s", name);
        if (name[0] == 'C') {
            geometry[i].type = 0;
            scanf("%d%d%d%d", &geometry[i].xc, &geometry[i].yc, &geometry[i].r, &geometry[i].c);
        } else if (name[0] == 'D') {
            geometry[i].type = 1;
            scanf("%d%d%d%d", &geometry[i].xc, &geometry[i].yc, &geometry[i].r, &geometry[i].c);
        } else if (name[0] == 'R') {
            geometry[i].type = 2;
            scanf("%d%d%d%d%d", &geometry[i].xc, &geometry[i].yc, &geometry[i].l, &geometry[i].w, &geometry[i].c);
        } else if (name[0] == 'T') {
            geometry[i].type = 3;
            scanf("%d%d%d%d", &geometry[i].xc, &geometry[i].yc, &geometry[i].w, &geometry[i].c);
        }
    }
}

void solve() {
    memset(ans, 0, sizeof(ans));

    for (int i = 0; i < n; i++) {
        build(0, m - 1, 1);
        for (int j = q - 1; j >= 0; j--) {
            int l, r;
            bool flag = false;
            if (geometry[j].type == 0) {  // Circle
                if (abs(i - geometry[j].xc) > geometry[j].r) continue;
                int t = sqrt(geometry[j].r * geometry[j].r - (i - geometry[j].xc) * (i - geometry[j].xc));
                l = geometry[j].yc - t;
                r = geometry[j].yc + t;
                flag = true;
            } else if (geometry[j].type == 1) {  // Diamond
                if (abs(i - geometry[j].xc) > geometry[j].r) continue;
                int t = geometry[j].r - abs(i - geometry[j].xc);
                l = geometry[j].yc - t;
                r = geometry[j].yc + t;
                flag = true;
            } else if (geometry[j].type == 2) {  // Rectangle
                if (i < geometry[j].xc || i > geometry[j].xc + geometry[j].l - 1) continue;
                l = geometry[j].yc;
                r = geometry[j].yc + geometry[j].w - 1;
                flag = true;
            } else if (geometry[j].type == 3) {  // Triangle
                if (i < geometry[j].xc || i - geometry[j].xc >= (geometry[j].w + 1) / 2) continue;
                int t = (geometry[j].w - 1) / 2 - (i - geometry[j].xc) ;
                l = geometry[j].yc - t;
                r = geometry[j].yc + t;
                flag = true;
            }
            if (!flag) continue;
            l = max(0, l);
            r = min(m - 1, r);
            if (l > r) continue;
            ans[geometry[j].c] += query(l, r, 1);
            insert(l, r, 1);
        }
    }

    for (int i = 1; i <= 9; i++) {
        if (i > 1) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");
}

int main() {
    while (~scanf("%d%d%d", &n, &m, &q)) {
        input();
        solve();
    }
    return 0;
}
