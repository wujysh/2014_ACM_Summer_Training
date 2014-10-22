#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int INF = 99999999;
const int MAXN = 100010;
const int MAXM = 200010;
struct Edge {
    int from, to, c, next;
    Edge(int u0 = 0, int v0 = 0, int c0 = 0, int next0 = 0) {
        from = u0;
        to = v0;
        c = c0;
        next = next0;
    }
} edge[MAXM];
int head[MAXN], tot;
int from, to, N, M, nCase;
int q[MAXN], cnt[MAXN], d[MAXN], low[MAXN], cur[MAXN];

void init() {
    memset(head, -1, sizeof(head));
    tot = 0;
}

void addEdge(int u, int v, int c) {
    edge[tot] = Edge(u, v, c, head[u]);
    head[u] = tot++;
    edge[tot] = Edge(v, u, c, head[v]);
    head[v] = tot++;
}

void input() {
    int westernmost = INF, easternmost = 0, s, t;

    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (x < westernmost) {
            westernmost = x;
            s = i;
        }
        if (x > easternmost) {
            easternmost = x;
            t = i;
        }
    }

    from = s;
    to = t;
    //addEdge(from, s, INF);
    //addEdge(t, to, INF);

    for (int i = 0; i < M; i++) {
        int l1, l2, c;
        scanf("%d%d%d", &l1, &l2, &c);
        addEdge(l1, l2, c);
        //addEdge(l2, l1, c);
    }
}



int maxflow(int s, int t, int n) {
    int *front = q, *rear = q;
    for(int i = 1; i <= n; i++) {
        d[i] = n;
        cnt[i] = 0;
    }
    cnt[n] = n - 1;
    cnt[0]++;
    d[t] = 0;
    *rear++ = t;
    while(front < rear) {      // 反向广搜，预处理好用于gap优化的
        // 记录高度数量的数组 cnt[]
        int v = *front++;
        for(int i = head[v]; i != -1; i = edge[i].next) {
            if(d[edge[i].to] == n && edge[i ^ 1].c > 0) { // 如果没采访过，且有边
                // 相连，入队
                d[edge[i].to] = d[v] + 1;
                cnt[n]--;
                cnt[d[edge[i].to]]++;
                *rear++ = edge[i].to;
            }
        }
    }
    int flow = 0, u = s, top = 0;
    low[0] = INF;
    for(int i = 1; i <= n; i++)
        cur[i] = head[i];  //  初始化当前弧为第一条邻接边
    while(d[s] < n) {      //  当 d[s]>=n 时，网络出现了gap,增广结束
        int &i = cur[u];  // 当前弧优化
        for(; i != -1; i = edge[i].next) { // 寻找最短增广路
            if(edge[i].c > 0 && d[u] == d[edge[i].to] + 1) { // 寻找最短增广路
                low[top + 1] = min(low[top], edge[i].c); // 更新路径最小流量
                q[++top] = i;
                u = edge[i].to;
                break;
            }
        }
        if(i != -1) {
            if(u == t) {      // 找到了增广路，修改路径上的边容量
                int minf = low[top];
                for(int p = 1, i; p <= top; ++p) {
                    i = q[p];
                    edge[i].c -= minf;
                    edge[i ^ 1].c += minf;
                }
                flow += minf;
                u = s;
                low[0] = INF;
                top = 0;
            }
        } else {
            int old_du = d[u];
            cnt[old_du]--;
            d[u] = n - 1;
            for(int i = head[u]; i != -1; i = edge[i].next) // 高度数组出现断层
                if(edge[i].c > 0 && d[u] > d[edge[i].to]) // 跟新最近的一个点为最短路上的点
                    d[u] = d[edge[i].to];
            cnt[++d[u]]++;          // 更新高度数量数组
            if(d[u] < n)
                cur[u] = head[u];
            if(u != s) {
                u = edge[q[top]].from;
                --top;
            }
            if(cnt[old_du] == 0) // gap 优化
                break;
        }
    }
    return flow;
}

void output() {
    printf("%d\n", maxflow(from, to, N));
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        init();
        input();
        output();
    }
    return 0;
}
