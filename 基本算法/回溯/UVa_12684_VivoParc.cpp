#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 110;
int ans[MAXN], n, cnt;
bool graph[MAXN][MAXN];
vector<int> child[MAXN];
char line[MAXN];

void init() {
    for (int i = 0; i < MAXN; i++) {
        child[i].clear();
    }
    memset(graph, false, sizeof(graph));
    memset(ans, 0, sizeof(ans));
}

void input() {
    getchar();
    int a, b;
    while (gets(line) && strlen(line)) {
        int a, b;
        sscanf(line, "%d-%d", &a, &b);
        if (a != b && !graph[a][b]) {
            child[a].push_back(b);
            child[b].push_back(a);
            graph[a][b] = graph[b][a] = true;
        }
    }
}

bool dfs(int x) {
    if (x == n+1) {
        return true;
    }

    for (int i = 1; i <= 4; i++) {
        bool flag = true;
        for (int j = 0; j < child[x].size(); j++) {
            int v = child[x][j];
            if (v < x && ans[v] == i) {
                flag = false;
                break;
            }
        }
        if (flag) {
            ans[x] = i;
            if (dfs(x+1)) return true;
        }
    }
    return false;
}

void solve() {
    dfs(0);

    if (cnt++) printf("\n");
    for (int i = 1; i <= n; i++) {
        printf("%d %d\n", i, ans[i]);
    }
}

int main() {
    while (~scanf("%d", &n)) {
        init();
        input();
        solve();
    }
    return 0;
}
