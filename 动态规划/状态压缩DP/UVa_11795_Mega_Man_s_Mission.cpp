#include <iostream>
using namespace std;

const int MAXN = 1 << 16;
int n, weapon[MAXN], temp[MAXN], nCase, cnt;
long long x, ans, dp[MAXN];

int ch2to10(long long x) {
    int t = 1, ans = 0;
    while (x) {
        ans += (x % 10) * t;
        x /= 10;
        t *= 2;
    }
    return ans;
}

void input() {
    cin >> n;
    cin >> x;
    weapon[0] = ch2to10(x);
    for (int i = 1; i <= n; i++) {
        cin >> x;
        temp[i] = ch2to10(x);
    }
}

long long DP(int x) {
    if (dp[x] != -1) return dp[x];
    dp[x] = 0;
    for (int i = 0; i < n; i++) {
        if (x & (1 << i)) {
            if (weapon[x - (1 << i)] & (1 << i)) {
                dp[x] += DP(x - (1 << i));
            }
        }
    }
    return dp[x];
}

void work() {
    dp[0] = 1;
    for (int i = 1; i < (1 << n); i++) {
        weapon[i] = weapon[0];
        dp[i] = -1;
        for (int j = n-1; j >= 0; j--) {
            if (i & (1 << j)) {
                weapon[i] |= temp[n-j];
            }
        }
    }
    ans = DP((1 << n) - 1);
}

void output() {
    cout << "Case " << ++cnt << ": " << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        input();
        work();
        output();
    }
    return 0;
}
