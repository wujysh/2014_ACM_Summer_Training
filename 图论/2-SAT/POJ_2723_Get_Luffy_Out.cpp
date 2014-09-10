#include <iostream>
#include <cstring>
#include <stack>
#include <vector>
using namespace std;

const int MAXN = 5000;
stack<int> st;
bool inStack[MAXN];
int dfn[MAXN], low[MAXN], belong[MAXN], dfn_cnt, cnt, N, M;
vector<int> child[MAXN];

struct Node {
    int a, b;
} key[MAXN], door[MAXN];

void init() {
    for (int i = 1; i <= 4*N; i++) {
        child[i].clear();
    }
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(belong, 0, sizeof(belong));
    memset(inStack, 0, sizeof(inStack));
    while (!st.empty()) st.pop();
    dfn_cnt = cnt = 0;
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

void build(int mid) {
    for (int i = 1; i <= N; i++) {
        child[key[i].a+1].push_back(key[i].b+2*N+1);
        child[key[i].b+1].push_back(key[i].a+2*N+1);
    }
    for (int i = 1; i <= mid; i++) {
        child[door[i].a+2*N+1].push_back(door[i].b+1);
        child[door[i].b+2*N+1].push_back(door[i].a+1);
    }
}

void input() {
    int a, b;
    for (int i = 1; i <= N; i++) {
        cin >> key[i].a >> key[i].b;
    }
    for (int i = 1; i <= M; i++) {
        cin >> door[i].a >> door[i].b;
    }
}

void solve() {
    int l = 1, r = M + 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        init();
        build(mid);
        for (int i = 1; i <= 4*N; i++) {
            if (!dfn[i]) {
                Tarjan(i);
            }
        }

        bool flag = true;
        for (int i = 1; i <= 2*N; i++) {
            if (belong[i] == belong[i+2*N]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    cout << l - 1 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> N >> M && (N || M)) {
        input();
        solve();
    }
    return 0;
}
