//#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 500010;
long long dp[MAXN], sum[MAXN], c[MAXN], q[MAXN], m;
int head, tail, n;

long long G(int x, int y) {
    return dp[x] - dp[y] + sum[x]*sum[x] - sum[y]*sum[y];
}

long long S(int x, int y) {
    return 2 * (sum[x] - sum[y]);
}

void init() {
    head = 0;  tail = 1;
    memset(dp, 0, sizeof(dp));
    memset(q, 0, sizeof(q));
    sum[0] = 0;
}

void input() {
    for (int i = 1; i <= n; i++) {
        scanf("%I64d", &c[i]);
        //cin >> c[i];
        sum[i] = sum[i-1] + c[i];
    }
}

void work() {
    for (int i = 1; i <= n; i++) {
        while (head+1 < tail && G(q[head+1], q[head]) <= sum[i] * S(q[head+1], q[head])) {
            head++;
        }
        //dp[i] = min(dp[j] + (sum[i] - sum[j])^2 + m);  (0 <= j < i)
        dp[i] = dp[q[head]] + (sum[i] - sum[q[head]])*(sum[i] - sum[q[head]]) + m;
        while (head+1 < tail && G(i, q[tail-1]) * S(q[tail-1], q[tail-2]) <= G(q[tail-1], q[tail-2]) * S(i, q[tail-1])) {
            tail--;
        }
        q[tail++] = i;
    }
}

void output() {
    //cout << dp[n] << endl;
    printf("%I64d\n", dp[n]);
}

int main() {
    //ios::sync_with_stdio(false);
    while (scanf("%d%d", &n, &m) == 2) {
    //while (cin >> n >> m) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
