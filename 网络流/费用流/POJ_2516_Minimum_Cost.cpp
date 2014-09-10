//#include <iostream>
#include <cstdio>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
using namespace std;

const int INF = 0x3f3f3f3f;
const double eps = 1e-8;
const int MAXN = 155;
const int MAXM = 10000;
struct Edge {
    int u, v, next;
    int c;
    int w;
    Edge(int u0 = 0, int v0 = 0, int c0 = 0, int w0 = 0, int next0 = 0) {
        u = u0;
        v = v0;
        c = c0;
        w = w0;
        next = next0;
    }
} edge[MAXM * 4];
int head[MAXN], cnt;

bool visited[MAXN];
int path[MAXN], from, to, N, M, K, needAll;
int dist[MAXN], ans, need[MAXN][MAXN], store[MAXN][MAXN], cost[MAXN][MAXN][MAXN];

void addEdge(int u, int v, int c, int w) {
    edge[cnt] = Edge(u, v, c, w, head[u]);
    head[u] = cnt++;
    edge[cnt] = Edge(v, u, 0, -w, head[v]);
    head[v] = cnt++;
}

void input() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= K; j++) {
            //cin >> need[i][j];
            scanf("%d", &need[i][j]);
        }
    }
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= K; j++) {
            //cin >> store[i][j];
            scanf("%d", &store[i][j]);
        }
    }
    for (int i = 1; i <= K; i++) {
        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= M; k++) {
                //cin >> cost[i][j][k];
                scanf("%d", &cost[i][j][k]);
            }
        }
    }

    from = 0;
    to = N + M + 1;
}

bool findPath() {
    queue <int> q;
    memset(visited, false, sizeof(visited));
    memset(path, -1, sizeof(path));
    fill(dist, dist + MAXN, INF);
    dist[from] = 0;
    visited[from] = true;
    q.push(from);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].v;
            if (edge[i].c > 0 && dist[u] + edge[i].w < dist[v]) {
                dist[v] = dist[u] + edge[i].w;
                path[v] = i;
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        visited[u] = false;
    }

    return dist[to] != INF;
}

int MinCostMaxFlow() {
    int offflow, maxflow = 0;
    int ret = 0;
    while (findPath()) {
        offflow = INF;
        for (int i = path[to]; i != -1; i = path[edge[i].u]) {
            offflow = min(offflow, edge[i].c);
        }
        for (int i = path[to]; i != -1; i = path[edge[i].u]) {
            edge[i].c -= offflow;
            edge[i ^ 1].c += offflow;
        }
        maxflow += offflow;
        ret += dist[to] * offflow;
    }
    return maxflow == needAll ? ret : -1;
}

void buildEdge(int k) {
    memset(head, -1, sizeof(head));
    cnt = 0;

    for (int i = 1; i <= M; i++) {
        addEdge(from, i, store[i][k], 0);
    }

    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            addEdge(i, j+M, INF, cost[k][j][i]);
        }
    }

    for (int i = 1; i <= N; i++) {
        addEdge(i+M, to, need[i][k], 0);
        needAll += need[i][k];
    }
}

void solve() {
    ans = 0;
    for (int i = 1; i <= K; i++) {
        needAll = 0;
        buildEdge(i);

        int minCost = MinCostMaxFlow();
        if (minCost == -1) {
            //cout << -1 << endl;
            printf("-1\n");
            return;
        } else {
            ans += minCost;
        }
    }
    //cout << ans << endl;
    printf("%d\n", ans);
}

int main() {
    //ios::sync_with_stdio(false);
    //while (cin >> N >> M >> K && (N || M || K)) {
    while (~scanf("%d%d%d", &N, &M, &K) && (N || M || K)) {
        input();
        solve();
    }
    return 0;
}
