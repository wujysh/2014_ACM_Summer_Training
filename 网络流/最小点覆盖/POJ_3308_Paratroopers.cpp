#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <cmath>
using namespace std;

const double INF = 1 << 30;
const int MAXN = 500;
struct Edge {
    int u, v, next;
    double c;
    Edge(int u0 = 0, int v0 = 0, double c0 = 0, int next0 = 0) {
        u = u0;
        v = v0;
        c = c0;
        next = next0;
    }
} edge[MAXN * 10];
int head[MAXN * 2], cnt;
bool visited[MAXN * 2];
int path[MAXN * 2], from, to, M, N, I, nCase;
double maxflow, offflow;

void init() {
    memset(head, -1, sizeof(head));
    cnt = 0;
    maxflow = 0.0;
}

void addEdge(int u, int v, double c) {
    edge[cnt] = Edge(u, v, c, head[u]);
    head[u] = cnt++;
    edge[cnt] = Edge(v, u, 0, head[v]);
    head[v] = cnt++;
}

void input() {
    cin >> M >> N >> I;

    from = 0;  to = M + N + 1;

    double x;
    for (int i = 1; i <= M; i++) {
        cin >> x;
        addEdge(from, i, log(x));
    }

    for (int i = 1; i <= N; i++) {
        cin >> x;
        addEdge(i+M, to, log(x));
    }

    for (int i = 1; i <= I; i++) {
        int a, b;
        cin >> a >> b;
        addEdge(a, b+M, INF);
    }
}

bool bfs() {
    int s = from, d;
    queue <int> q;
    q.push(s);
    memset(visited, false, sizeof(visited));
    visited[s] = true;
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
    cout << fixed << setprecision(4) << exp(maxflow) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
