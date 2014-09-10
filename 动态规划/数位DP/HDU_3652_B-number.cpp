#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 10;
int dp[MAXN][13][2][2], n, m, digit[MAXN], len;

int DP(int n, int j, bool k, bool flag, bool limit) {
    if (n == 0) return j == 0 && k;
    if (!limit && dp[n][j][k][flag] != -1) return dp[n][j][k][flag];

    int ans = 0, maxDigit = limit ? digit[n] : 9;
    for (int i = 0; i <= maxDigit; i++) {
        ans += DP(n-1, (j*10+i) % 13, k || (flag && i == 3), i == 1, limit && i == digit[n]);
    }

    if (!limit) dp[n][j][k][flag] = ans;
    return ans;
}

void init() {
    memset(dp, -1, sizeof(dp));
}

int solve(int x) {
    len = 0;
    while (x) {
        digit[++len] = x % 10;
        x /= 10;
    }
    return DP(len, 0, false, false, true);
}

int main() {
    ios::sync_with_stdio(false);
    init();
    while (cin >> n) {
        cout << (solve(n) - solve(0)) << endl;
    }
    return 0;
}
