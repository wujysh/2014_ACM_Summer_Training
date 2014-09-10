#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

const int MAXN = 1010;
stack<int> st;
bool inStack[MAXN];
int dfn[MAXN], low[MAXN], belong[MAXN], inDegree[MAXN], dfn_cnt, cnt, N, M, nCase;
vector<int> child[MAXN], child2[MAXN];

void init() {
    for (int i = 1; i <= N; i++) {
        child[i].clear();
        child2[i].clear();
    }
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(belong, 0, sizeof(belong));
    memset(inStack, 0, sizeof(inStack));
    memset(inDegree, 0, sizeof(inDegree));
    while (!st.empty()) st.pop();
    dfn_cnt = 1;
    cnt = 0;
}

void Tarjan(int u) {
    dfn[u] = low[u] = dfn_cnt++;
    st.push(u);
    inStack[u] = true;

    for (int i = 0; i < child[u].size(); i++) {
        int v = child[u][i];
        if (!dfn[v]) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        cnt++;
        while (true) {
            int t = st.top();
            st.pop();
            inStack[t] = false;
            belong[t] = cnt;
            if (t == u) break;
        }
    }
}

bool TopoSort() {
    queue<int> q;
    for (int i = 1; i <= cnt; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
            if (q.size() > 1) return false;
        }
    }
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = 0; i < child2[cur].size(); i++) {
            int v = child2[cur][i];
            inDegree[v]--;
            if (inDegree[v] == 0) {
                q.push(v);
                if (q.size() > 1) return false;
            }
        }
    }
    return true;
}

void input() {
    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        int u, v;
        cin >> u >> v;
        child[u].push_back(v);
    }
}

void solve() {
    for (int i = 1; i <= N; i++) {
        if (!dfn[i]) {
            Tarjan(i);
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < child[i].size(); j++) {
            int u = belong[i], v = belong[child[i][j]];
            if (u != v) {
                child2[u].push_back(v);
                inDegree[v]++;
            }
        }
    }

    if (TopoSort()) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        init();
        input();
        solve();
    }
    return 0;
}
