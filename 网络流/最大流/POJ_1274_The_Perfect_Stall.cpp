#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 5000;
struct Edge {
    int u, v, c, next;
    Edge(int u0 = 0, int v0 = 0, int c0 = 0, int next0 = 0) {
        u = u0;
        v = v0;
        c = c0;
        next = next0;
    }
} edge[MAXN * 10];
int head[MAXN * 2], cnt;
bool visited[MAXN * 2];
int path[MAXN * 2], from, to, maxflow, offflow, n, m;

void init() {
    memset(head, -1, sizeof(head));
    cnt = 0;
    maxflow = 0;
}

void addEdge(int u, int v, int c) {
    edge[cnt] = Edge(u, v, c, head[u]);
    head[u] = cnt++;
    edge[cnt] = Edge(v, u, 0, head[v]);
    head[v] = cnt++;
}

void input() {
    from = 0;
    to = 410;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        for (int j = 1; j <= x; j++) {
            int y;
            cin >> y;
            addEdge(i, y+200, 1);
        }
        addEdge(from, i, 1);
    }
    for (int i = 1; i <= m; i++) {
        addEdge(i+200, to, 1);
    }
}

bool bfs() {
    int s = from, d;
    queue <int> q;
    q.push(s);
    memset(visited, false, sizeof(visited));
    while (!q.empty()) {
        s = q.front();
        q.pop();
        visited[s] = true;
        for (int i = head[s]; i != -1; i = edge[i].next) {
            d = edge[i].v;
            if (!visited[d] && edge[i].c > 0) {
                path[d] = i;
                q.push(d);
                if (d == to) return true;
            }
        }
    }
    return false;
}

void work() {
    while (bfs()) {
        offflow = INF;
        for (int i = to; i != from; i = edge[path[i]].u) {
            if (edge[path[i]].c < offflow)
                offflow = edge[path[i]].c;
        }
        for (int i = to; i != from; i = edge[path[i]].u) {
            edge[path[i]].c -= offflow;
            edge[path[i] ^ 1].c += offflow;
        }
        maxflow += offflow;
    }
}

void output() {
    cout << maxflow << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> m) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
