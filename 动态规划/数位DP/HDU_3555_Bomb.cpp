#include <iostream>
#include <cstring>
using namespace std;

int digit[20], len, nCase;
long long n, dp[20][2];

long long DP(int n, bool flag, bool limit) {
    if (n == 0) return 1;
    if (!limit && dp[n][flag] != -1) return dp[n][flag];

    long long ans = 0;
    int maxDigit = limit ? digit[n] : 9;
    for (int i = 0; i <= maxDigit; i++) {
        if (flag && i == 9) continue;
        ans += DP(n-1, i == 4, limit && i == digit[n]);
    }

    if (!limit) dp[n][flag] = ans;
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
    return DP(len, false, true);
}

int main() {
    ios::sync_with_stdio(false);
    init();
    cin >> nCase;
    while (nCase--) {
        cin >> n;
        cout << n - (solve(n) - solve(0)) << endl;
    }
    return 0;
}
