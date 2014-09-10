#include <iostream>
#include <cstring>
using namespace std;

const int MAXM = 15;
const int MAXN = 1 << 15;
int dp[MAXM][MAXN], row[MAXN], ans, M, N;

void init() {
    memset(dp, 0, sizeof(dp));
    ans = 0;
}

void input() {
    for (int i = 0; i < M; i++) {
        row[i] = 0;
        for (int j = N-1; j >= 0; j--) {
            int k;
            cin >> k;
            row[i] |= (k << j);
        }
        //cout << row[i] << endl;
    }
}

void work() {
    for (int i = 0; i < (1 << N); i++) {
        if ((i & (i << 1)) == 0) {
            if ((row[0] & i) == i) {
                dp[0][i] = 1;
            } else {
                dp[0][i] = 0;
            }
        }
    }

    for (int i = 1; i < M; i++) {
        for (int j = 0; j < (1 << N); j++) {
            if ((j & (j << 1)) == 0) {  // no adjacent
                if ((row[i] & j) == j) {  // all futile
                    for (int k = 0; k < (1 << N); k++) {
                        if ((j & k) == 0) {  // no conflict
                            dp[i][j] = (dp[i][j] + dp[i-1][k]) % 100000000;
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < (1 << N); i++) {
        ans = (ans + dp[M-1][i]) % 100000000;
    }
}

void output() {
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> M >> N) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
