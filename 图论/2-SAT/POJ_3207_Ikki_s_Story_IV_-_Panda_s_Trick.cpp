#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;

const int MAXN = 1010;
int dfn[MAXN], low[MAXN], belong[MAXN], id_cnt, cnt, n, m;
bool inStack[MAXN];
stack<int> st;

struct Wire {
    int a, b;
    Wire() {}
    Wire(int _a, int _b) : a(_a), b(_b) {}
} wire[MAXN];
vector<int> child[MAXN];

void Tarjan(int u) {
    dfn[u] = low[u] = id_cnt++;
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
            int cur = st.top();
            st.pop();
            inStack[cur] = false;
            belong[cur] = cnt;
            if (cur == u) break;
        }
    }
}

void solve() {
    for (int i = 1; i <= m; i++) {
        cin >> wire[i].a >> wire[i].b;
        if (wire[i].a > wire[i].b) {
            swap(wire[i].a, wire[i].b);
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            if (i != j && wire[i].a < wire[j].a && wire[i].b > wire[j].a && wire[i].b < wire[j].b) {
                child[i].push_back(j+m);
                child[i+m].push_back(j);
                child[j].push_back(i+m);
                child[j+m].push_back(i);
            }
        }
    }

    for (int i = 1; i <= 2*m; i++) {
        if (!dfn[i]) {
            Tarjan(i);
        }
    }

    for (int i = 1; i <= m; i++) {
        if (belong[i] == belong[i+m]) {
            cout << "the evil panda is lying again" << endl;
            return;
        }
    }
    cout << "panda is telling the truth..." << endl;
}

void init() {
    for (int i = 1; i <= 2*m; i++) {
        child[i].clear();
    }
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(belong, 0, sizeof(belong));
    memset(inStack, 0, sizeof(inStack));
    while (!st.empty()) st.pop();
    id_cnt = 1;
    cnt = 0;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> m) {
        init();
        solve();
    }
    return 0;
}
