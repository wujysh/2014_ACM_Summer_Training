//#include <iostream>
//#include <iomanip>
#include <cstring>
#include <cstdio>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 1010;
int R, C;
double p[MAXN][MAXN][3], dp[MAXN][MAXN];

void init() {
    memset(dp, 0, sizeof(dp));
}

void input() {
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            scanf("%lf %lf %lf", &p[i][j][0], &p[i][j][1], &p[i][j][2]);
            //cin >> p[i][j][0] >> p[i][j][1] >> p[i][j][2];
        }
    }
}

void work() {
    dp[R][C] = 0;
    for (int i = R; i >= 1; i--) {
        for (int j = C; j >= 1; j--) {
            if (i == R && j == C) continue;
            dp[i][j] = p[i][j][1] * dp[i][j+1] + p[i][j][2] * dp[i+1][j];
            dp[i][j] += 2;
            if (p[i][j][0] == 1) {
                dp[i][j] = INF;
            } else {
                dp[i][j] /= 1 - p[i][j][0];
            }
        }
    }
}

void output() {
    printf("%.3f\n", dp[1][1]);
    //cout << fixed << setprecision(3) << dp[1][1] << endl;
}

int main() {
    //ios::sync_with_stdio(false);
    //while (cin >> R >> C) {
    while (scanf("%d %d", &R, &C) == 2) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
