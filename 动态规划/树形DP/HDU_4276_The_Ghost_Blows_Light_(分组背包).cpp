#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#define max(a,b) ((a) > (b) ? (a) : (b))
using namespace std;

const int MAXN = 105;
const int MAXT = 505;
int N, T, rest, pre[MAXN], dp[MAXN][MAXT], dis[MAXN][MAXN], ans[MAXT];
vector<int> path, child[MAXN];

void init() {
    for (int i = 0; i <= N; i++) {
        child[i].clear();
    }
    path.clear();
    memset(dp, -1, sizeof(dp));
    memset(ans, 0, sizeof(ans));
    pre[1] = -1;
    rest = T;
}

void input() {
    for (int i = 0; i < N - 1; i++) {
        int a, b, t;
        scanf("%d%d%d", &a, &b, &t);
        child[a].push_back(b);
        child[b].push_back(a);
        dis[a][b] = dis[b][a] = t;
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &dp[i][0]);
    }
}

void DFS(int x, int father) {
    if (x == N) {
        return;
    }
    for (int i = 0; i < child[x].size(); i++) {
        int c = child[x][i];
        if (c == father) continue;
        pre[c] = x;
        DFS(c, x);
    }
}

void DP(int x, int father, int forbidden) {
    for (int k = 0; k < child[x].size(); k++) {
        int c = child[x][k];
        if (c == father || c == forbidden) continue;
        DP(c, x, -1);

        for (int i = rest; i >= 0; i--) {
            if (dp[x][i] == -1) continue;
            for (int j = rest; j >= 0; j--) {
                int a = i + j + 2 * dis[x][c];
                if (a <= rest && dp[c][j] != -1) {
                    dp[x][a] = max(dp[x][a], dp[x][i] + dp[c][j]);
                }
            }
        }
    }
}

void solve() {
    DFS(1, -1);

    int x = N;
    path.push_back(-1);
    while (x != -1) {
        path.push_back(x);
        rest -= dis[x][pre[x]];
        x = pre[x];
    }
    path.push_back(-1);

    if (rest < 0) {
        printf("Human beings die in pursuit of wealth, and birds die in pursuit of food!\n");
        return;
    }

    for (int i = 1; i < path.size() - 1; i++) {
        DP(path[i], path[i + 1], path[i - 1]);
    }

    int Max = 0;
    for (int i = 1; i < path.size() - 1; i++) {
        for (int j = rest; j >= 0; j--) {
            if (ans[j] == 0 && j != 0) continue;
            for (int k = rest - j; k >= 0; k--) {
                if (dp[path[i]][k] != -1) {
                    ans[j + k] = max(ans[j + k], ans[j] + dp[path[i]][k]);
                }
            }
        }
    }
    for (int i = 0; i <= rest; i++) {
        Max = max(Max , ans[i]);
    }

    printf("%d\n", Max);
}

int main() {
    while (~scanf("%d%d", &N, &T)) {
        init();
        input();
        solve();
    }
    return 0;
}
