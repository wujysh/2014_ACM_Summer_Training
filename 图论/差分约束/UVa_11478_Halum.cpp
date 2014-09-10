//#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

const int MAXN = 510;
const int MAXM = 3010;
const int INF = 10005;
struct Node {
    int u, v, d;
    Node() {}
    Node(int _v, int _d) : v(_v), d(_d) {}
} edge[MAXM];
vector<Node> child[MAXN];
int V, E, dist[MAXN], cnt[MAXN], limit;
bool inQueue[MAXN];

inline void init() {
    for (int i = 1; i <= V; i++) {
        child[i].clear();
    }
}

void input() {
    for (int i = 1; i <= E; i++) {
        //cin >> edge[i].u >> edge[i].v >> edge[i].d;
        scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].d);
    }
}

inline void build(int mid) {
    init();
    for (int i = 1; i <= V; i++) {
        child[0].push_back(Node(i, 0));
    }
    for (int i = 1; i <= E; i++) {
        child[edge[i].u].push_back(Node(edge[i].v, edge[i].d - mid));
    }
}

inline bool spfa(int u) {
    for (int i = 1; i <= V; i++) {
        dist[i] = INF;
        cnt[i] = 0;
        inQueue[i] =false;
    }
    queue<int> q;

    q.push(u);
    inQueue[u] = true;
    dist[u] = 0;
    cnt[u]++;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        inQueue[cur] = false;
        for (int i = 0; i < child[cur].size(); i++) {
            int v = child[cur][i].v;
            if (dist[v] > dist[cur] + child[cur][i].d) {
                dist[v] = dist[cur] + child[cur][i].d;
                if (!inQueue[v]) {
                    q.push(v);
                    inQueue[v] = true;
                    cnt[v]++;
                    if (cnt[v] > limit) return false;
                }
            }
        }
    }
    return true;
}

void solve() {
    limit = sqrt(V) + 1;

    build(1);
    if (!spfa(0)) {
        printf("No Solution\n");
        //cout << "No Solution" << endl;
        return;
    }

    build(INF);
    if (spfa(0)) {
        printf("Infinite\n");
        //cout << "Infinite" << endl;
        return;
    }

    int l = 1, r = INF;
    while (l < r) {
        int mid = (l + r) >> 1;
        build(mid);
        if (spfa(0)) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    printf("%d\n", l-1);
    //cout << l - 1 << endl;
}

int main() {
    //ios::sync_with_stdio(false);
    //while (cin >> V >> E) {
    while (~scanf("%d%d", &V, &E)) {
        input();
        solve();
    }
    return 0;
}
