#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 1000;
const int MAXM = 330000;
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
bool visited[MAXN], vis[MAXN];
int path[MAXN], d[MAXN], from, to, maxflow, offflow, n, m, k, sumR, sumC;
int r[MAXN], c[MAXN], graph[MAXN][MAXN];

void init() {
    memset(head, -1, sizeof(head));
    cnt = 0;
    maxflow = 0;
    sumR = sumC = 0;
}

void addEdge(int u, int v, int c) {
    edge[cnt] = Edge(u, v, c, head[u]);
    head[u] = cnt++;
    edge[cnt] = Edge(v, u, 0, head[v]);
    head[v] = cnt++;
}

void input() {
    from = 0;
    to = n + m + 1;

    for (int i = 1; i <= n; i++) {
        scanf("%d", &r[i]);
        sumR += r[i];
        addEdge(from, i, r[i]);
        for (int j = 1; j <= m; j++) {
            addEdge(i, n+j, k);
        }
    }
    for (int j = 1; j <= m; j++) {
        scanf("%d", &c[j]);
        sumC += c[j];
        addEdge(n+j, to, c[j]);
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

bool can(int u, int father) {
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].v;
        if (v == 0 || v == father || edge[i].c <= 0) continue;
        if (vis[v]) return true;
        vis[v] = true;
        if (can(v, u)) return  true;
        vis[v] = false;
    }
    return false;
}

void output() {
    if (sumR != sumC) {
        printf("Impossible\n");
    } else {
        int ans = dinic();
        memset(vis,false,sizeof vis);
        if (ans == sumR) {
            bool flag = false;
            for (int i = 1; i <= n; i++) {
                if (!vis[i]) {
                    if (can(i, -1)) {
                        flag = true;
                        break;
                    }
                }
            }
            if(flag) {
                printf("Not Unique\n");
            }else {
                printf("Unique\n");
                for (int i = 1; i <= n; i++) {
                    for (int j = head[i]; j != -1; j = edge[j].next) {
                        if (edge[j].v != 0) {
                            graph[i][edge[j].v - n] = edge[j ^ 1].c;
                        }
                    }
                }
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j <= m; j++) {
                        if (j > 1) printf(" ");
                        printf("%d", graph[i][j]);
                    }
                    printf("\n");
                }
            }
        } else {
            printf("Impossible\n");
        }
    }
}

int main() {
    while (~scanf("%d%d%d", &n, &m, &k)) {
        init();
        input();
        output();
    }
    return 0;
}
