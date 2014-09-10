#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

const long long INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 1010;
const int MAXM = 5010;
struct Edge {
    int u, v, next;
    long long c, w;
    Edge(int u0 = 0, int v0 = 0, long long c0 = 0, long long w0 = 0, int next0 = 0) {
        u = u0;
        v = v0;
        c = c0;
        w = w0;
        next = next0;
    }
} edge[MAXM * 4];
int head[MAXN], cnt;

bool visited[MAXN];
int path[MAXN], from, to, F, P, D;
long long dist[MAXN], ans;

void init() {
    memset(head, -1, sizeof(head));
    cnt = 0;
    D = 0;
}

void addEdge(int u, int v, long long c, long long w) {
    edge[cnt] = Edge(u, v, c, w, head[u]);
    head[u] = cnt++;
    edge[cnt] = Edge(v, u, 0, -w, head[v]);
    head[v] = cnt++;
}

void input() {
    from = 0;
    to = F + 1;
    for (int i = 1; i <= F; i++) {
        int num1, num2;
        cin >> num1 >> num2;
        D += num1;
        addEdge(from, i, num1, 0);
        addEdge(i, to, num2, 0);
    }
    for (int i = 0; i < P; i++) {
        int x, y;
        long long cost;
        cin >> x >> y >> cost;
        addEdge(x, y, INF, cost);
        addEdge(y, x, INF, cost);
    }
}

bool findPath() {
    queue <int> q;
    memset(visited, false, sizeof(visited));
    memset(path, -1, sizeof(path));
    memset(dist, 0x3f, sizeof(dist));

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

long long MinCostMaxFlow() {
    long long offflow, maxflow = 0, ret = 0;

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
        //ret += dist[to] * offflow;
        ret = max(ret, dist[to]);
    }

    return maxflow == D ? ret : -1;
}

void work() {
    ans = MinCostMaxFlow();
}

void output() {
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> F >> P) {
        init();
        input();
        work();
        output();
    }
    return 0;
}

