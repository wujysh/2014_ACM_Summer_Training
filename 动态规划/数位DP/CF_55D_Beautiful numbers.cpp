#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 20;
int digit[MAXN], lcm_index[2525], len, cnt, nCase;
long long dp[MAXN][50][2525], l, r;

int GCD(int a, int b) {
    return b == 0 ? a : GCD(b, a % b);
}

int LCM(int a, int b) {
    if (b == 0) return a;
    return a / GCD(a, b) * b;
}

long long DP(int n, int lcm, int sum, bool limit) {
    if (n == 0) return sum % lcm == 0;
    if (!limit && dp[n][lcm_index[lcm]][sum] != -1) return dp[n][lcm_index[lcm]][sum];

    long long ans = 0;
    int maxDigit = limit ? digit[n] : 9;
    for (int i = 0; i <= maxDigit; i++) {
        ans += DP(n-1, LCM(lcm, i), (sum * 10 + i) % 2520, limit && i == digit[n]);
    }

    if (!limit) dp[n][lcm_index[lcm]][sum] = ans;
    return ans;
}

void init() {
    memset(dp, -1, sizeof(dp));
    cnt = 0;
    for (int i = 1; i <= 2520; i++) {
        if (2520 % i == 0) {
            lcm_index[i] = cnt++;
        }
    }
}

long long solve(long long x) {
    len = 0;
    while (x) {
        digit[++len] = x % 10;
        x /= 10;
    }
    return DP(len, 1, 0, true);
}

int main() {
    ios::sync_with_stdio(false);
    init();
    cin >> nCase;
    while (nCase--) {
        cin >> l >> r;
        cout << solve(r) - solve(l-1) << endl;
    }
    return 0;
}
