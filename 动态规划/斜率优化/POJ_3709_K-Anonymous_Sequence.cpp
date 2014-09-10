//#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 500010;
long long dp[MAXN], sum[MAXN], a[MAXN], q[MAXN];
int head, tail, n, k, nCase;

long long G(long long x, long long y) {
    return dp[y] - dp[x] + y*a[y+1] - x*a[x+1] + sum[x] - sum[y];
}

long long S(long long x, long long y) {
    return a[y+1] - a[x+1];
}

void init() {
    head = 0;  tail = 1;
    memset(dp, 0, sizeof(dp));
    memset(q, 0, sizeof(q));
    sum[0] = 0;
}

void input() {
    scanf("%d%d", &n, &k);
    //cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        //cin >> a[i];
        sum[i] = sum[i-1] + a[i];
    }
}

void work() {
    for (int i = 1; i <= n; i++) {
        while (head+1 < tail && G(q[head], q[head+1]) <= i * S(q[head], q[head+1])) {
            head++;
        }
        //dp[i] = min(dp[j] + sum[i] - sum[j] + a[j+1]*(i-j));  j = q[head];  (j - i >= k)
        dp[i] = dp[q[head]] + sum[i] - sum[q[head]] - a[q[head]+1]*(i-q[head]);
        if (i - k + 1 >= k) {
            q[tail++] = i - k + 1;
        }
        while (head+2 < tail && G(q[tail-2], q[tail-1]) * S(q[tail-3], q[tail-2]) <= G(q[tail-3], q[tail-2]) * S(q[tail-2], q[tail-1])) {
            q[tail-2] = q[tail-1];
            tail--;
        }
    }
}

void output() {
    printf("%lld\n", dp[n]);
    //cout << dp[n] << endl;
}

int main() {
    //ios::sync_with_stdio(false);
    scanf("%d", &nCase);
    //cin >> nCase;
    while (nCase--) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
