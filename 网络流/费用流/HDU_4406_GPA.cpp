#include <cstdio>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

const int INF = 0x3f3f3f3f;
const double eps = 1e-8;
const int MAXN = 100;
const int MAXM = 2000;
struct Edge {
    int u, v, next;
    int c;
    double w;
    Edge() {}
    Edge(int _u, int _v, int _c, double _w, int _next) : u(_u), v(_v), c(_c), w(_w), next(_next) {}
} edge[MAXM * 2];
int head[MAXN], cnt;

bool visited[MAXN];
int path[MAXN], from, to, N, K, M, sumCredit;
double dist[MAXN], ans;

struct Course {
    int credit, score;
} course[MAXN];

void addEdge(int u, int v, int c, double w) {
    edge[cnt] = Edge(u, v, c, w, head[u]);
    head[u] = cnt++;
    edge[cnt] = Edge(v, u, 0, -w, head[v]);
    head[v] = cnt++;
}

void init() {
    memset(head, -1, sizeof(head));
    cnt = 0;
    sumCredit = ans = 0;
}

double F(int x, int w) {
    return (4.0 - 3.0 * (100 - x) * (100 - x) / 1600) * w;
}

void input() {
    from = 0;
    to = M + N + 1;

    for (int i = 1; i <= M; i++) {
        scanf("%d", &course[i].credit);
        sumCredit += course[i].credit;
    }
    for (int i = 1; i <= M; i++) {
        scanf("%d", &course[i].score);
        if (course[i].score < 60) {
            addEdge(from, i, 60-course[i].score, 1.0*INF);
            double pre = F(60, course[i].credit), cur;
            for (int j = 61; j <= 100; j++) {
                cur = F(j, course[i].credit);
                addEdge(from, i, 1, cur-pre);
                pre = cur;
            }
        } else {
            double pre = F(course[i].score, course[i].credit), cur;
            for (int j = course[i].score+1; j <= 100; j++) {
                cur = F(j, course[i].credit);
                addEdge(from, i, 1, cur-pre);
                pre = cur;
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            bool whether;
            scanf("%d", &whether);
            if (whether) {
                addEdge(j, i+M, K, 0);
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        addEdge(i+M, to, K, 0);
    }
}

bool findPath() {
    queue <int> q;
    memset(visited, false, sizeof(visited));
    memset(path, -1, sizeof(path));
    fill(dist, dist + MAXN, -1.0*INF);
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
    return ret;
}

void solve() {
    MaxCostMaxFlow();

    for (int i = head[from]; i != -1; i = edge[i].next) {
        course[edge[i].v].score += edge[i ^ 1].c;
    }

    for (int i = 1; i <= M; i++) {
        if (course[i].score < 60) {
            printf("0.000000\n");
            return;
        }
        ans += F(course[i].score, course[i].credit) / sumCredit;
    }
    printf("%.6lf\n", ans);
}

int main() {
    while (~scanf("%d%d%d", &N, &K, &M) && (N || K || M)) {
        init();
        input();
        solve();
    }
    return 0;
}
