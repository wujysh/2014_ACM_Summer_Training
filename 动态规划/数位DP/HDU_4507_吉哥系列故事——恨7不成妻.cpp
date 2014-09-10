#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 20;
const int MOD = 1000000007;
int digit[MAXN], len, nCase;
long long pow10[MAXN], l, r;
struct Node {
    long long cnt, sum, sum2;
    Node() : cnt(0), sum(0), sum2(0) {}
    Node(long long _cnt, long long _sum, long long _sum2) : cnt(_cnt), sum(_sum), sum2(_sum2) {}
} dp[MAXN][10][10];

Node DP(int n, int j, int k, bool first) {
    if (n == 0) return Node(j && k, 0, 0);
    if (!first && dp[n][j][k].cnt != -1) return dp[n][j][k];

    Node cur;
    int maxDigit = first ? digit[n] : 9;
    for (int i = 0; i <= maxDigit; i++) {
        if (i == 7) continue;
        Node next = DP(n-1, (j+i)%7, (k*10+i)%7, first && i == digit[n]);

        cur.cnt += next.cnt;
        cur.cnt %= MOD;
        cur.sum += i * pow10[n-1] % MOD * next.cnt % MOD + next.sum;
        cur.sum %= MOD;
        cur.sum2 += i*i * pow10[n-1] % MOD * pow10[n-1] % MOD * next.cnt % MOD + 2 * i * pow10[n-1] % MOD * next.sum % MOD + next.sum2;
        cur.sum2 %= MOD;
    }

    if (!first) dp[n][j][k] = cur;
    return cur;
}

void init() {
    pow10[0] = 1;
    for (int i = 1; i < 20; i++) {
        pow10[i] = pow10[i-1] * 10 % MOD;
    }
    memset(dp, -1, sizeof(dp));
}

long long solve(long long x) {
    len = 0;
    while (x) {
        digit[++len] = x % 10;
        x /= 10;
    }
    return DP(len, 0, 0, true).sum2;
}

int main() {
    ios::sync_with_stdio(false);
    init();
    cin >> nCase;
    while (nCase--) {
        cin >> l >> r;
        cout << (solve(r) - solve(l-1) + MOD) % MOD << endl;
    }
    return 0;
}
