//#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 1010;
const int INF = 0x3f3f3f3f;
int graph[MAXN][MAXN], edge[MAXN], queue[MAXN], n, X, Y, Z;
bool used[MAXN], pass[MAXN], more;

struct Household {
    int x, y, z;
    Household() {}
    Household(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
} household[MAXN];

inline void combine(int id, int &sum) {
    int total = 0, from;
    for (; id != 0 && !pass[id]; id = edge[id]) {
        queue[total++] = id;
        pass[id] = true;
    }
    for (from = 0; from < total && queue[from] != id; from++);
    if (from == total) return;
    more = true;
    for (int i = from; i < total; i++) {
        sum += graph[edge[queue[i]]][queue[i]];
        if (i != from) {
            used[queue[i]] = true;
            for (int j = 1; j <= n; j++) {
                if (!used[j]) {
                    if (graph[queue[i]][j] < graph[id][j]) {
                        graph[id][j] = graph[queue[i]][j];
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i] && i != id) {
            for (int j = from; j < total; j++) {
                int k = queue[j];
                if (graph[i][id] > graph[i][k] - graph[edge[k]][k]) {
                    graph[i][id] = graph[i][k] - graph[edge[k]][k];
                }
            }
        }
    }
}

int mdst(int root) {
    int sum = 0;
    memset(used, false, sizeof(used));
    for (more = true; more; ) {
        more = false;
        memset(edge, 0, sizeof(edge));
        for (int i = 1; i <= n; i++) {
            if (!used[i] && i != root) {
                int k = 0;
                for (int j = 1; j <= n; j++) {
                    if (!used[j] && i != j) {
                        if (k == 0 || graph[j][i] < graph[k][i]) {
                            k = j;
                        }
                    }
                }
                edge[i] = k;
            }
        }
        memset(pass, false, sizeof(pass));
        for (int i = 1; i <= n; i++) {
            if (!used[i] && !pass[i] && i != root) {
                combine(i, sum);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i] && i != root) {
            sum += graph[edge[i]][i];
        }
    }
    return sum;
}

inline int dist(Household h1, Household h2) {
    return fabs(h2.x - h1.x) + fabs(h2.y - h1.y) + fabs(h2.z - h1.z);
}

void solve() {
    memset(graph, 0x3f, sizeof(graph));

    for (int i = 1; i <= n; i++) {
        //cin >> household[i].x >> household[i].y >> household[i].z;
        scanf("%d%d%d", &household[i].x, &household[i].y, &household[i].z);
        graph[n+1][i] = household[i].z * X;
    }
    for (int u = 1; u <= n; u++) {
        int k;
        //cin >> k;
        scanf("%d", &k);
        for (int j = 1; j <= k; j++) {
            int v;
            //cin >> v;
            scanf("%d", &v);
            if (u == v) continue;
            int dis = dist(household[u], household[v]) * Y;
            if (household[v].z > household[u].z) {
                graph[u][v] = dis + Z;
            } else {
                graph[u][v] = dis;
            }
        }
    }

    //cout << mdst(++n) << endl;
    printf("%d\n", mdst(++n));
}

int main() {
    //ios::sync_with_stdio(false);
    //while (cin >> n >> X >> Y >> Z && (n || X || Y || Z)) {
    while (~scanf("%d%d%d%d", &n, &X, &Y, &Z) && (n || X || Y || Z)) {
        solve();
    }
    return 0;
}
