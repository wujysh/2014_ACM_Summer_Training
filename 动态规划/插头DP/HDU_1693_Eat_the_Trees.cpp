#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 13;
int nCase, n, m, cnt;
long long dp[MAXN][MAXN][1 << MAXN];
bool hasTree[MAXN][MAXN];

void input() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &hasTree[i][j]);
        }
    }
}

void solve() {
    memset(dp, 0, sizeof(dp));
    dp[0][m][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int st = 0; st < (1 << m); st++) {
            dp[i][0][st << 1] = dp[i-1][m][st];
        }
        for (int j = 1; j <= m; j++) {
            int a = 1 << (j-1), b = 1 << j;
            for (int st = 0; st < (1 << (m+1)); st++) {
                if (hasTree[i][j]) {
                    if ((st & a) && (st & b)) {
                        dp[i][j][st] += dp[i][j-1][st - a - b];
                    } else if (!(st & a) && !(st & b)) {
                        dp[i][j][st] += dp[i][j-1][st | a | b];
                    } else {
                        dp[i][j][st] = dp[i][j-1][st] + dp[i][j-1][st ^ a ^ b];
                    }
                } else {
                    if ((st & a) || (st & b)) {
                        dp[i][j][st] = 0;
                    } else {
                        dp[i][j][st] = dp[i][j-1][st];
                    }
                }
            }
        }
    }
    printf("Case %d: There are %I64d ways to eat the trees.\n", ++cnt, dp[n][m][0]);
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        input();
        solve();
    }
    return 0;
}
