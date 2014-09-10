#include <iostream>
#include <cstring>
using namespace std;

const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, -1, 0, 1};
const int MAXN = 110;
int dp[MAXN][MAXN], R, C, height[MAXN][MAXN], ans;

void input() {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> height[i][j];
        }
    }
}

int DP(int x, int y) {
    if (dp[x][y] != -1) return dp[x][y];

    dp[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < R && ny >= 0 && ny < C && height[nx][ny] < height[x][y]) {
            dp[x][y] = max(dp[x][y], DP(nx, ny)+1);
        }
    }
    return dp[x][y];
}

void solve() {
    ans = 0;
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            ans = max(ans, DP(i, j));
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> R >> C) {
        input();
        solve();
    }
    return 0;
}
