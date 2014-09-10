#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 110;
const int MAXM = 10010;
const int INF = 0x3f3f3f3f;
int N, M, X, T, sum[MAXN][MAXM], ans;
int dp[MAXN][MAXM], q[MAXM][2], head, tail;

void init() {
    ans = -INF;
}

void input() {
    for (int i = 1; i <= N; i++) {
        sum[i][0] = 0;
        for (int j = 1; j <= M; j++) {
            int score;
            scanf("%d", &score);
            sum[i][j] = sum[i][j-1] + score;
            dp[i][j] = -INF;
        }
    }
}

void work() {
    for (int i = X; i >= max(X-T, 1); i--) {
        dp[1][i] = sum[1][X] - sum[1][i-1];
    }
    for (int i = X; i <= min(X+T, M); i++) {
        dp[1][i] = sum[1][i] - sum[1][X-1];
    }

    for (int i = 2; i <= N; i++) {
        // from left
        head = tail = 0;
        for (int j = 1; j <= M; j++) {
            int tmp = dp[i-1][j] - sum[i][j-1];
            while (head < tail && q[tail-1][1] <= tmp) {
                tail--;
            }
            q[tail][0] = j;
            q[tail++][1] = tmp;

            while (head < tail && q[head][0] < j - T) {
                head++;
            }

            dp[i][j] = max(dp[i][j], q[head][1] + sum[i][j]);
        }

        // from right
        head = tail = 0;
        for (int j = M; j >= 1; j--) {
            int tmp = dp[i-1][j] + sum[i][j];
            while (head < tail && q[tail-1][1] <= tmp) {
                tail--;
            }
            q[tail][0] = j;
            q[tail++][1] = tmp;

            while (head < tail && q[head][0] > j + T) {
                head++;
            }

            dp[i][j] = max(dp[i][j], q[head][1] - sum[i][j-1]);
        }
    }

    for (int j = 1; j <= M; j++) {
        ans = max(ans, dp[N][j]);
    }
}

void output() {
    printf("%d\n", ans);
}

int main() {
    while (scanf("%d%d%d%d", &N, &M, &X, &T) == 4) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
