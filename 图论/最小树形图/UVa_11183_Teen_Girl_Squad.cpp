#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 1010;
const int INF = 0x3f3f3f3f;
int graph[MAXN][MAXN], edge[MAXN], queue[MAXN], n, m, cnt, nCase;
bool used[MAXN], pass[MAXN], more;

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

void solve() {
    memset(graph, 0x3f, sizeof(graph));
    cin >> n;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u == v) continue;
        graph[u+1][v+1] = min(graph[u+1][v+1], w);
    }

    int ans = mdst(1);

    cout << "Case #" << ++cnt << ": ";
    if (ans < INF) {
        cout << ans << endl;
    } else {
        cout << "Possums!" << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        solve();
    }
    return 0;
}
