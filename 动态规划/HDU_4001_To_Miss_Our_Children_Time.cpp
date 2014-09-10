#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 2010;
int n;

struct Node {
    long long a, b, c, d, s;
    bool operator<(const Node &p) const {
        if (a != p.a) return a < p.a;
        if (b != p.b) return b < p.b;
        return d > p.d;
    }
} node[MAXN];

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n && n) {
        for (int i = 0; i < n; i++) {
            cin >> node[i].a >> node[i].b >> node[i].c >> node[i].d;
            if (node[i].a < node[i].b) {
                swap(node[i].a, node[i].b);
            }
            node[i].s = node[i].a * node[i].b;
        }
        sort(node, node + n);
        long long ans = node[0].c;
        for (int i = 1; i < n; i++) {
            long long h = 0;
            for (int j = 0; j < i; j++) {
                if (node[i].d == 0) {
                    if (node[i].a >= node[j].a && node[i].b >= node[j].b) {
                        h = max(h, node[j].c);
                    }
                } else if (node[i].d == 1) {
                    if (node[i].a >= node[j].a && node[i].b >= node[j].b && node[i].s > node[j].s) {
                        h = max(h, node[j].c);
                    }
                } else if (node[i].d == 2) {
                    if (node[i].a > node[j].a && node[i].b > node[j].b) {
                        h = max(h, node[j].c);
                    }
                }
            }
            node[i].c += h;
            ans = max(ans, node[i].c);
        }

        cout << ans << endl;
    }
    return 0;
}
