#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int MAXN = 100010;
int N, M, fly[MAXN];
double dp[MAXN];
bool visited[MAXN];

void init() {
    memset(fly, -1, sizeof(fly));
    memset(visited, false, sizeof(visited));
}

void input() {
    for (int i = 0; i < M; i++) {
        int x, y;
        cin >> x >> y;
        fly[x] = y;
    }
}

double DP(int from) {
    if (from >= N) return dp[from] = 0;
    if (visited[from]) return dp[from];
    visited[from] = true;
    if (fly[from] != -1) {
        return dp[from] = DP(fly[from]);
    } else {
        dp[from] = 0;
        for (int i = 1; i <= 6; i++) {
            dp[from] += 1.0 / 6.0 * (DP(from+i) + 1);
        }
        return dp[from];
    }
}

void output() {
    cout << fixed << setprecision(4) << DP(0) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> N >> M && (N || M)) {
        init();
        input();
        output();
    }
    return 0;
}
