#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 11;
const int INF = 0x3f3f3f3f;
int N, M, dp[MAXN][1 << MAXN], cost[MAXN], interest[MAXN][MAXN], bonus[MAXN][MAXN], w[MAXN][1 << MAXN];
vector<int> state[1 << MAXN];

void init() {
    for (int i = 0; i < (1 << 10); i++) {
        for (int j = i+1; j < (1 << 10); j++) {
            if ((i & j) == i) {
                state[i].push_back(j);
            }
        }
    }
}

void input() {
    for (int i = 0; i < M; i++) {
        scanf("%d", &cost[i]);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &interest[i][j]);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &bonus[i][j]);
        }
    }
}

void solve() {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < (1 << 11); j++) {
            dp[i][j] = -INF;
            w[i][j] = -INF;
        }
    }
    int len = 1 << N;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < len; j++) {
            int index[MAXN], cnt = 0, sum = 0;
            for (int k = 0; k < N; k++) {
                if (j & (1 << k)) {
                    index[cnt++] = k;
                    sum += interest[k][i];
                }
            }
            for (int p = 0; p < cnt; p++) {
                for (int q = p+1; q < cnt; q++) {
                    sum += bonus[index[p]][index[q]];
                }
            }
            w[i][j] = sum - cost[i] * cnt;
        }
    }

    int ans = -INF;

    for (int i = 0; i < (1 << N); i++) {
        dp[0][i] = w[0][i];
        ans = max(ans, dp[0][i]);
    }
    for (int i = 1; i < M; i++) {
        for (int j = 0; j < (1 << N); j++) {
            dp[i][j] = dp[i-1][j] + w[i][j];
            ans = max(ans, dp[i][j]);
            for (int k = 0; k < state[j].size(); k++) {
                dp[i][j] = max(dp[i][j], dp[i-1][state[j][k]] + w[i][j]);
                ans = max(ans, dp[i][j]);
            }
        }
    }

    if (ans <= 0) {
        printf("STAY HOME\n");
    } else {
        printf("%d\n", ans);
    }
}

int main() {
    init();
    while (~scanf("%d%d", &N, &M) && (N || M)) {
        input();
        solve();
    }
    return 0;
}
