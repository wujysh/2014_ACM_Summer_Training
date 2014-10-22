#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 110;
const int dx[8] = {-1, -1, 0, 1, 1,  1,  0, -1};
const int dy[8] = { 0,  1, 1, 1, 0, -1, -1, -1};
char graph[MAXN][MAXN];
int dp[MAXN][MAXN][10][2], n, ans;

void init() {
    memset(dp, -1, sizeof(dp));
}

void input() {
    getchar();
    for (int i = 0; i < n; i++) {
        scanf("%s", graph[i]);
    }
}

bool judge(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= n) return false;
    if (graph[x][y] == '#') return false;
    return true;
}

int DP(int x, int y, int pre, int flag) {
    int ans = 0;

    if (pre == -1) {
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (judge(nx, ny)) {
                ans = max(ans, DP(nx, ny, i, 0));
            }
        }
        return ans+1;
    }

    if (dp[x][y][pre][flag] != -1) {
        return dp[x][y][pre][flag];
    }

    int nx = x + dx[pre];
    int ny = y + dy[pre];
    if (judge(nx, ny)) {
        ans = max(ans, DP(nx, ny, pre, flag));
    }

    if (!flag) {
        int a = (pre + 6) % 8;
        nx = x + dx[a], ny = y + dy[a];
        if (judge(nx, ny)) {
            ans = max(ans, DP(nx, ny, a, 1));
        }

        int b = (pre + 2) % 8;
        nx = x + dx[b], ny = y + dy[b];
        if (judge(nx, ny)) {
            ans = max(ans, DP(nx, ny, b, 1));
        }
    }

    return dp[x][y][pre][flag] = ans + 1;
}

void solve() {
    ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == '.') {
                ans = max(ans, DP(i, j, -1, 0));
            }
        }
    }
    printf("%d\n", ans);
}

int main() {
    while (~scanf("%d", &n) && n) {
        init();
        input();
        solve();
    }
    return 0;
}
