//#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 250;
struct Edge {
    int u, v, c, next;
    Edge(int u0 = 0, int v0 = 0, int c0 = 0, int next0 = 0) {
        u = u0;
        v = v0;
        c = c0;
        next = next0;
    }
} edge[45000];
int head[MAXN], cnt;
bool visited[MAXN];
int path[MAXN], graph[MAXN][MAXN], dis[MAXN][MAXN], src, to, max_flow, K, C, M;

void addEdge(int u, int v, int c) {
    edge[cnt] = Edge(u, v, c, head[u]);
    head[u] = cnt++;
    edge[cnt] = Edge(v, u, 0, head[v]);
    head[v] = cnt++;
}

void input() {
    for (int i = 1; i <= K + C; i++) {
        for (int j = 1; j <= K + C; j++) {
            //cin >> graph[i][j];
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == 0) {
                graph[i][j] = INF;
            }
        }
    }
}

bool bfs() {
    int s = src, d;
    queue <int> q;
    q.push(s);
    visited[s] = true;
    memset(visited, false, sizeof(visited));
    while (!q.empty()) {
        s = q.front();
        q.pop();
        //visited[s] = true;
        for (int i = head[s]; i != -1; i = edge[i].next) {
            d = edge[i].v;
            if (!visited[d] && edge[i].c > 0) {
                path[d] = i;
                //q.push(d);
                if (d == to) return true;
                q.push(d);
                visited[d] = true;
            }
        }
    }
    return false;
}

int run_flow() {
    int maxflow = 0;
    while (bfs()) {
        int offflow = INF;
        for (int i = to; i != src; i = edge[path[i]].u) {
            if (edge[path[i]].c < offflow)
                offflow = edge[path[i]].c;
        }
        for (int i = to; i != src; i = edge[path[i]].u) {
            edge[path[i]].c -= offflow;
            edge[path[i] ^ 1].c += offflow;
        }
        maxflow += offflow;
    }
    return maxflow;
}

void SPFA(int u) {
    memset(visited, false, sizeof(visited));
    queue<int> q;
    q.push(u);
    visited[u] = true;
    dis[u][u] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        visited[cur] = false;
        for (int i = 1; i <= K + C; i++) {
            if (dis[u][i] > dis[u][cur] + graph[cur][i]) {
                dis[u][i] = dis[u][cur] + graph[cur][i];
                if (!visited[i]) {
                    q.push(i);
                    visited[i] = true;
                }
            }
        }
    }
}

inline void buildEdge(int len) {
    memset(head, -1, sizeof(head));
    cnt = 0;

    src = 0;
    to = K + C + 1;

    for (int i = 1; i <= K; i++) {
        addEdge(src, i, M);
        for (int j = K+1; j <= K+C; j++) {
            if (dis[i][j] <= len) {
                addEdge(i, j, 1);
            }
        }
    }
    for (int i = K+1; i <= K+C; i++) {
        addEdge(i, to, 1);
    }
}

void solve() {
    memset(dis, 0x3f, sizeof(dis));
    int l = 0, r = 0;
    for (int i = 1; i <= K; i++) {
        SPFA(i);
        for (int j = K + 1; j <= K + C; j++) {
            r = max(r, dis[i][j]);
        }
    }
    buildEdge(r);
    max_flow = run_flow();
    while (l < r) {
        int mid = (l + r) >> 1;
        buildEdge(mid);
        int cur_flow = run_flow();
        if (cur_flow < max_flow) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    //cout << l << endl;
    printf("%d\n", l);
}

int main() {
    //ios::sync_with_stdio(false);
    //while (cin >> K >> C >> M) {
    while (~scanf("%d%d%d", &K, &C, &M)) {
        input();
        solve();
    }
    return 0;
}
