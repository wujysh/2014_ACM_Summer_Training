#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 20;
long long dp[MAXN][MAXN][2000], A, B, digit[MAXN], len, nCase;

long long DP(int n, int p, int sum, bool limit) {
    if (n == 0) return sum == 0;
    if (sum < 0) return 0;
    if (!limit && dp[n][p][sum] != -1) return dp[n][p][sum];

    long long ans = 0;
    int maxDigit = limit ? digit[n] : 9;
    for (int i = 0; i <= maxDigit; i++) {
        ans += DP(n-1, p, sum + (n-p)*i, limit && i == digit[n]);
    }

    if (!limit) dp[n][p][sum] = ans;
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

    long long ans = 0;
    for (int i = 1; i <= len; i++) {
        ans += DP(len, i, 0, true) - 1;  // remove all zeros
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    init();
    cin >> nCase;
    while (nCase--) {
        cin >> A >> B;
        cout << (solve(B) - solve(A-1)) << endl;
    }
    return 0;
}
