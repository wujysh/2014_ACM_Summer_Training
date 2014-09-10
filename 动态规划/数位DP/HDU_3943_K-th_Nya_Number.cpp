#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 20;
long long dp[MAXN][10], A, B, digit[MAXN], len, nCase, cnt;

long long DP(int n, int j, bool limit) {
    if (n == 0) return j == 0;
    if (!limit && dp[n][j] != -1) return dp[n][j];

    long long ans = 0;
    int maxDigit = limit ? digit[n] : 9;
    for (int i = 0; i <= maxDigit; i++) {
        ans += DP(n-1, (j+i) % 10, limit && i == digit[n]);
    }

    if (!limit) dp[n][j] = ans;
    return ans;
}

void init() {
    memset(dp, -1, sizeof(dp));
}

long long solve(long long x) {
    len = 0;
    while (x) {
        digit[++len] = x % 10;
        x /= 10;
    }
    return DP(len, 0, true);
}

int main() {
    ios::sync_with_stdio(false);
    init();
    cin >> nCase;
    while (nCase--) {
        cin >> A >> B;
        cout << "Case #" << ++cnt << ": " << (solve(B) - solve(A-1)) << endl;
    }
    return 0;
}
