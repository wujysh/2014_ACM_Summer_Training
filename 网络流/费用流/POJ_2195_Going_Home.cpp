#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
using namespace std;

const long long INF = 1 << 30;
const double eps = 1e-8;
const int MAXN = 250;
const int MAXM = 10000;
struct Edge {
    int u, v, next;
    long long c;
    int w;
    Edge(int u0 = 0, int v0 = 0, long long c0 = 0, int w0 = 0, int next0 = 0) {
        u = u0;
        v = v0;
        c = c0;
        w = w0;
        next = next0;
    }
} edge[MAXM * 4];
int head[MAXN], cnt;

bool visited[MAXN];
int path[MAXN], from, to, N, M;
int dist[MAXN], ans;

struct Node {
    int x, y;
    Node() {}
    Node(int _x, int _y) : x(_x), y(_y) {}
} Hs[MAXN], Ms[MAXN];
int cntH, cntM;

void init() {
    memset(head, -1, sizeof(head));
    cnt = cntH = cntM = 0;
}

void addEdge(int u, int v, long long c, int w) {
    edge[cnt] = Edge(u, v, c, w, head[u]);
    head[u] = cnt++;
    edge[cnt] = Edge(v, u, 0, -w, head[v]);
    head[v] = cnt++;
}

void input() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            char ch;
            cin >> ch;
            if (ch == 'm') {
                Ms[++cntM] = Node(i, j);
            } else if (ch == 'H') {
                Hs[++cntH] = Node(i, j);
            }
        }
    }

    from = 0;
    to = cntM + cntH + 1;

    for (int i = 1; i <= cntM; i++) {
        addEdge(from, i, 1, 0);
        addEdge(i+cntM, to, 1, 0);
        for (int j = 1; j <= cntH; j++) {
            int dis = abs(Ms[i].x - Hs[j].x) + abs(Ms[i].y - Hs[j].y);
            addEdge(i, j+cntM, 1, dis);
        }
    }
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
    long long offflow, maxflow = 0;
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
    return maxflow == cntM ? ret : -1;
}

void work() {
    ans = MinCostMaxFlow();
}

void output() {
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> N >> M && (N || M)) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
