#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 110, MAXM = 11;
vector<int> state;
int dp[MAXN][MAXN][MAXN], graph[MAXN], n, m;

void init() {
    for (int i = 0; i < (1 << 10); i++) {
        if ((i & (i >> 1)) == 0 && (i & (i >> 2)) == 0) {
            state.push_back(i);
        }
    }
    graph[0] = (1 << 10) - 1;
}

void input() {
    for (int i = 1; i <= n; i++) {
        cin.ignore();
        graph[i] = 0;
        for (int j = 0; j < m; j++) {
            char ch;
            cin >> ch;
            if (ch == 'P') {
                graph[i] |= (1 << j);
            }
        }
    }
}

void solve() {
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < state.size() && state[i] < (1 << m); i++) {
        if ((state[i] & graph[1]) == state[i]) {
            int cnt = 0;
            for (int j = 0; j < m; j++) {
                if (state[i] & (1 << j)) {
                    cnt++;
                }
            }
            for (int j = 0; j < state.size() && state[j] < (1 << m); j++) {
                if ((state[i] & state[j]) == 0) {
                    dp[1][i][j] = cnt;
                }
            }
        }
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < state.size() && state[j] < (1 << m); j++) {
            if ((state[j] & graph[i]) == state[j]) {
                int cnt = 0;
                for (int k = 0; k < m; k++) {
                    if (state[j] & (1 << k)) {
                        cnt++;
                    }
                }
                for (int k = 0; k < state.size() && state[k] < (1 << m); k++) {
                    if ((state[k] & graph[i-1]) == state[k] && ((state[k] & state[j]) == 0)) {
                        for (int l = 0; l < state.size() && state[l] < (1 << m); l++) {
                            if ((state[l] & graph[i-2]) == state[l] && ((state[l] & state[k]) == 0) && ((state[l] & state[j]) == 0)) {
                                dp[i][j][k] = max(dp[i][j][k], dp[i-1][k][l]);
                            }
                        }
                        dp[i][j][k] += cnt;
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < state.size() && state[i] < (1 << m); i++) {
        if ((state[i] & graph[n]) == state[i]) {
            for (int j = 0; j < state.size() && state[j] < (1 << m); j++) {
                if ((state[j] & graph[n-1]) == state[j]) {
                    ans = max(ans, dp[n][i][j]);
                }
            }
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    init();
    while (cin >> n >> m) {
        input();
        solve();
    }
    return 0;
}
