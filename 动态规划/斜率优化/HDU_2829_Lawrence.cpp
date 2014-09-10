#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 1010;
int nCase, cnt, n, m, j, head, tail;
int v[MAXN], sum[MAXN], sum2[MAXN], q[MAXN];
double dp[MAXN][MAXN];

int Q(int x, int y) {
    return 2*dp[x][j-1] - 2*dp[y][j-1] + sum[x]*sum[x] - sum[y]*sum[y] + sum2[x] - sum2[y];
}

int S(int x, int y) {
    return 2 * (sum[x] - sum[y]);
}

void init() {
    cnt++;
    memset(dp, 0, sizeof(dp));
    sum[0] = sum2[0] = 0;
}

void input() {
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        sum[i] = sum[i-1] + v[i];
        sum2[i] = sum2[i-1] + v[i]*v[i];
    }
}

void work() {
    for (int i = 1; i <= n; i++) {
        dp[i][0] = 0.5 * ((sum[i] - sum[0])*(sum[i] - sum[0]) - sum2[i] + sum2[0]);
        //cout << dp[i][0] << endl;
    }
    for (j = 1; j <= m; j++) {
        memset(q, 0, sizeof(q));
        head = tail = 0;
        q[tail++] = 1;

        for (int i = 2; i <= n; i++) {
            while (head+1 < tail && Q(q[head+1], q[head]) <= sum[i] * S(q[head+1], q[head])) {
                head++;
            }
            //dp[i][j] = min(dp[k][j-1] + 0.5 * ((sum[i] - sum[k])^2 - sum2[i] + sum2[k]));  (0 <= k < i)
            dp[i][j] = dp[q[head]][j-1] + 0.5 * ((sum[i] - sum[q[head]])*(sum[i] - sum[q[head]]) - sum2[i] + sum2[q[head]]);
            cout<<j<<" "<<i<<" "<<dp[i][j]<<endl;
            while (head+1 < tail && Q(q[tail-2], q[tail-1]) * S(q[tail-1], i) >= Q(q[tail-1], i) * S(q[tail-2], q[tail-1])) {
                tail--;
            }
            q[tail++] = i;
        }
    }
}

void output() {
    printf("%.0lf\n", dp[n][m]);
}

int main() {
    while (scanf("%d%d", &n, &m) == 2 && (n || m)) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
