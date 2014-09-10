#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 20;
const int INF = 0x3f3f3f3f;
int graph[MAXN][MAXN], weight[MAXN], dis[MAXN], pre[MAXN], n, m, ans;
long long ansEdge, ansNode;
bool valid[MAXN], v[MAXN];

int prim() {
    memset(v, false, sizeof(v));
    int u;
    for (int i = 1; i <= n; i++) {
        if (valid[i]) {
            u = i;
            break;
        }
    }
    v[u] = true;
    int edgeSum = 0;
    for (int i = 1; i <= n; i++) {
        if (valid[i]) {
            dis[i] = graph[u][i];
            pre[i] = u;
        }
    }
    for (int i = 1; i < m; i++) {
        u = -1;
        for (int j = 1; j <= n; j++) {
            if (valid[j] && !v[j]) {
                if (u == -1 || dis[u] > dis[j])
                    u = j;
            }
        }
        edgeSum += graph[pre[u]][u];
        v[u] = true;
        for (int j = 1; j <= n; j++) {
            if (valid[j] && !v[j]) {
                if (dis[j] > graph[u][j]) {
                    dis[j] = graph[u][j];
                    pre[j] = u;
                }
            }
        }
    }
    return edgeSum;
}

void init() {
    ansEdge = INF;
    ansNode = 0;
}

void input() {
    for (int i = 1; i <= n; i++) {
        cin >> weight[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> graph[i][j];
            if (graph[i][j] == 0) {
                graph[i][j] = INF;
            }
        }
    }
}

void work() {
    for (int i = (1 << m) - 1; i < (1 << n); i++) {
        int cnt = 0;
        long long edge_cur = 0, node_cur = 0;
        memset(valid, false, sizeof(valid));
        for (int j = 1; j <= n; j++) {
            if (i & (1 << (j-1))) {
                cnt++;
                valid[j] = true;
                node_cur += weight[j];
            }
        }

        if (cnt == m) {
            edge_cur = prim();
            if (edge_cur * ansNode < ansEdge * node_cur) {
                ansEdge = edge_cur;
                ansNode = node_cur;
                ans = i;
            }
        }
    }
}

void output() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (ans & (1 << (i-1))) {
            if (cnt++) cout << " ";
            cout << i;
        }
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> m && (n || m)) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
