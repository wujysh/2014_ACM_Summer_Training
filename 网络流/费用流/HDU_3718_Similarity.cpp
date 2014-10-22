#include <cstdio>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <queue>
#include <map>
using namespace std;

const int INF = 0x3f3f3f3f;
const double eps = 1e-8;
const int MAXN = 10010;
const int MAXK = 30;
const int MAXM = 3000;
struct Edge {
    int u, v, next;
    int c;
    double w;
    Edge() {}
    Edge(int _u, int _v, int _c, double _w, int _next) : u(_u), v(_v), c(_c), w(_w), next(_next) {}
} edge[MAXM * 2];
int head[MAXN], cnt;

bool visited[MAXN];
int path[MAXN], from, to, N, K, M, nCase;
double dist[MAXN], ans;
map<char, int> mapA, mapB;
int A[MAXN], B[MAXN], C[MAXK][MAXK];

void addEdge(int u, int v, int c, double w) {
    edge[cnt] = Edge(u, v, c, w, head[u]);
    head[u] = cnt++;
    edge[cnt] = Edge(v, u, 0, -w, head[v]);
    head[v] = cnt++;
}

void input() {
    cin >> N >> K >> M;

    from = 0;
    to = K + K + 1;

    mapA.clear();
    for (int i = 1; i <= N; i++) {
        char ch;
        cin >> ch;
        if (mapA.find(ch) == mapA.end()) {
            mapA[ch] = mapA.size();
        }
        A[i] = mapA[ch];
    }
}

bool findPath() {
    queue <int> q;
    memset(visited, false, sizeof(visited));
    memset(path, -1, sizeof(path));
    fill(dist, dist + MAXN, -1.0 * INF);
    dist[from] = 0;
    visited[from] = true;
    q.push(from);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        visited[u] = false;

        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].v;
            if (edge[i].c > 0 && dist[u] + edge[i].w > dist[v]) {
                dist[v] = dist[u] + edge[i].w;
                path[v] = i;
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    return dist[to] != -1.0 * INF;
}

double MaxCostMaxFlow() {
    int offflow, maxflow = 0;
    double ret = 0;
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
    return maxflow == K ? ret : -1;
}

void solve() {
    for (int i = 0; i < M; i++) {
        memset(head, -1, sizeof(head));
        cnt = 0;
        mapB.clear();
        memset(C, 0, sizeof(C));

        for (int j = 1; j <= N; j++) {
            char ch;
            cin >> ch;
            if (mapB.find(ch) == mapB.end()) {
                mapB[ch] = mapB.size();
            }
            B[j] = mapB[ch];
        }

        for (int j = 1; j <= N; j++) {
            C[A[j]][B[j]]++;
        }
        for (int j = 1; j <= K; j++) {
            addEdge(from, j, 1, 0);
            addEdge(K + j, to, 1, 0);
            for (int k = 1; k <= K; k++) {
                addEdge(j, K + k, 1, C[j][k]);
            }
        }

        cout << fixed << setprecision(4) << MaxCostMaxFlow() / N << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        input();
        solve();
    }
    return 0;
}
