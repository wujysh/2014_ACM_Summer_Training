#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

const int MAXN = 110;
struct Node {
    long long a, b, c, d;
    bool operator < (const Node &t) const {
        if (c == t.c) {
            return d > t.d;
        }
        return c > t.c;
    }
} node[MAXN];
int n;

int main() {
    while (~scanf("%d", &n) && n) {
        for (int i = 0; i < n; i++) {
            scanf("%lld%lld%lld", &node[i].a, &node[i].b, &node[i].c);
            node[i].d = node[i].a * node[i].b * node[i].c;
        }
        sort(node, node+n);
        printf("%lld\n", node[0].d);
    }
    return 0;
}
