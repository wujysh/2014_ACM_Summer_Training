#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 1010;
struct Computer {
    int x, y;
} c[MAXN];

vector<int> path[MAXN];
bool repaired[MAXN];
int n, d, father[MAXN], rank_set[MAXN];

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
    for (int i = 0; i < MAXN; i++) {
        path[i].clear();
    }
    memset(repaired, false, sizeof(repaired));
}

void input() {
    scanf("%d%d", &n, &d);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &c[i].x, &c[i].y);
    }
}

int dis(int i, int j) {
    return (c[i].x - c[j].x)*(c[i].x - c[j].x) + (c[i].y - c[j].y)*(c[i].y - c[j].y);
}

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            if (dis(i, j) <= d*d) {
                path[i].push_back(j);
                path[j].push_back(i);
            }
        }
    }

    char op[2];
    int p, q;
    while (~scanf("%s", op)) {
        if (op[0] == 'O') {
            scanf("%d", &p);
            repaired[p] = true;
            for (int i = 0; i < path[p].size(); i++) {
                int x = path[p][i];
                if (repaired[x]) {
                    //cout << "union " << p << " " << x << endl;
                    union_set(p, x);
                }
            }
        } else if (op[0] == 'S') {
            scanf("%d%d", &p, &q);
            //cout << "find " << p << " " << q << endl;
            //cout << find_set(p)  << " " << find_set(q) << endl;
            if (find_set(p) == find_set(q)) {
                printf("SUCCESS\n");
            } else {
                printf("FAIL\n");
            }
        }
    }
}

int main() {
    input();
    init();
    solve();
    return 0;
}
