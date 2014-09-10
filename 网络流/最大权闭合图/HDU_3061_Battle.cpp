#include <iostream>
//#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 550;
const int MAXM = 605000;
struct Edge {
    int u, v, c, next;
    Edge(int u0 = 0, int v0 = 0, int c0 = 0, int next0 = 0) {
        u = u0;
        v = v0;
        c = c0;
        next = next0;
    }
} edge[MAXM];
int head[MAXN], cnt;
bool visited[MAXN];
int path[MAXN], d[MAXN], from, to, maxflow, offflow, n, m, ans;

void init() {
    memset(head, -1, sizeof(head));
    cnt = 0;
    maxflow = 0;
    ans = 0;
}

void addEdge(int u, int v, int c) {
    edge[cnt] = Edge(u, v, c, head[u]);
    head[u] = cnt++;
    edge[cnt] = Edge(v, u, 0, head[v]);
    head[v] = cnt++;
}

void input() {
    from = 0;
    to = n + 1;

    for (int i = 1; i <= n; i++) {
        int w;
        cin >> w;
        if (w > 0) {
            addEdge(from, i, w);
            ans += w;
        } else if (w < 0) {
            addEdge(i, to, -w);
        }
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        addEdge(a, b, INF);
    }
}

bool bfs() {
    memset(d, 0, sizeof(d));
    queue<int> q;
    q.push(from);
    d[from] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].v;
            if (edge[i].c && !d[v]) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    return d[to];
}

int dfs(int x, int pf) {
    if (x == to) return pf;
    int ret = 0;
    for (int i = head[x]; i != -1 && pf ; i = edge[i].next) {
        int v = edge[i].v;
        if (edge[i].c && d[v] == d[x] + 1) {
            int p = dfs(v, min(edge[i].c, pf));
            edge[i].c -= p;
            edge[i ^ 1].c += p;
            ret += p;
            pf -= p;
        }
    }
    if (!ret) d[x] = -2;
    return ret;
}

int dinic() {
    int ret = 0;
    while (bfs()) ret += dfs(from, INF);
    return ret;
}

void output() {
    cout << ans - dinic() << endl;
    //printf("%d\n", dinic());
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> m) {
    //while (~scanf("%d %d", &n, &m)) {
        init();
        input();
        output();
    }
    return 0;
}
