#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 110;
struct Edge {
    int u, v, c, next;
    Edge(int u0 = 0, int v0 = 0, int c0 = 0, int next0 = 0) {
        u = u0;  v = v0;  c = c0;  next = next0;
    }
} edge[MAXN * 20], edge_backup[MAXN * 20];
int head[MAXN * 2], head_backup[MAXN * 2], cnt, cnt_backup;
bool visited[MAXN * 2];
int path[MAXN * 2], from, to, N, M, ans_number, ans_cost;

struct Bridge {
    int u, v, w;
    Bridge(int u0 = 0, int v0 = 0, int w0 = 0) {
        u = u0;  v = v0;  w = w0;
    }
};
vector<Bridge> bridge;

void init() {
    memset(head, -1, sizeof(head));
    cnt = 0;
    bridge.clear();
    ans_number = 0;
}

void addEdge(int u, int v, int c) {
    edge[cnt] = Edge(u, v, c, head[u]);
    head[u] = cnt++;
    edge[cnt] = Edge(v, u, 0, head[v]);
    head[v] = cnt++;
}

void input() {
    from = 0;
    to = N + 1;

    for (int i = 1; i <= N; i++) {
        int x;
        cin >> x;
        if (x) {
            addEdge(from, i, x);
        }
    }
    for (int i = 0; i < M; i++) {
        int u, v, w, p;
        cin >> u >> v >> w >> p;
        if (p < 0) {
            addEdge(u, to, w);
            addEdge(u, v, INF);
        } else if (p == 0) {
            addEdge(u, v, INF);
        } else {
            bridge.push_back(Bridge(u, v, w));
        }
    }

    memcpy(edge_backup, edge, sizeof(edge));
    memcpy(head_backup, head, sizeof(head));
    cnt_backup = cnt;
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
    int m = bridge.size();
    //cout << m << endl;
    for (int i = 0; i < (1 << m); i++) {
        int cost = 0, maxflow = 0;

        //cout << "i: " << i << endl;

        for (int j = 0; j < m; j++) {
            if (i & (1 << j)) {
                addEdge(bridge[j].u, bridge[j].v, INF);
                cost += bridge[j].w;
            } else {
                addEdge(bridge[j].u, bridge[j].v, 1);
            }
        }

        //cout << "cost: " << cost << endl;
        //for (int k = 0; k < cnt; k++) {
        //    cout << edge[k].u << " " << edge[k].v << " " << edge[k].c << endl;
        //}

        while (bfs()) {
            int offflow = INF;
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

        //cout << "maxflow: " << maxflow << endl;

        if (maxflow > ans_number) {
            ans_number = maxflow;
            ans_cost = cost;
        } else if (maxflow == ans_number) {
            if (cost < ans_cost) {
                ans_cost = cost;
            }
        }

        memcpy(edge, edge_backup, sizeof(edge));
        memcpy(head, head_backup, sizeof(head));
        cnt = cnt_backup;
    }
}

void output() {
    if (ans_number) {
        cout << ans_number << " " << ans_cost << endl;
    } else {
        cout << "Poor Heaven Empire" << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> N >> M) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
