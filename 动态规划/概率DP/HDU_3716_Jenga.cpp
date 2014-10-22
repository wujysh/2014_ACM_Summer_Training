#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 2, MAXA = 20, MAXBC = 30, MAXT = 3;
int n0, nCase;
double dp[MAXA][MAXBC][MAXBC][MAXT], b[MAXN][MAXT], d[MAXN][MAXT];

void input() {
    scanf("%d", &n0);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%lf%lf", &b[i][j], &d[i][j]);
        }
    }
}

inline double P(int who, int i, int n) {
    double ret = b[who][i] - n * d[who][i];
    if (ret > 1.0) {
        return 1.0;
    } else if (ret < 0.0) {
        return 0.0;
    } else {
        return ret;
    }
}

double DP(int A, int B, int C, int top) {
    if (dp[A][B][C][top] >= 0) return dp[A][B][C][top];
    if (A == 0 && C == 0) return dp[A][B][C][top] = 0.0;

    int D = 3*n0 - 3*(A+1) - 2*B - 2*C - top;
    int n = A+1 + B + C + D + (top > 0);
    int who = (6*n0 - 6*(A+1) - 3*B - 3*C - 2*top) % 2;  // 0-Alice, 1-Charles

    int nA = A, nTop = top;
    if (nTop == 2) nA++;
    nTop = (nTop + 1) % 3;

    double ret = 0.0;
    if (A > 0) {
        ret = max(ret, P(who, 0, n) * (1.0 - DP(nA-1, B+1, C, nTop)));
        ret = max(ret, P(who, 1, n) * (1.0 - DP(nA-1, B, C+1, nTop)));
    }
    if (C > 0) {
        ret = max(ret, P(who, 2, n) * (1.0 - DP(nA, B, C-1, nTop)));
    }
    return dp[A][B][C][top] = ret;
}

void solve() {
    for (int i = 0; i < MAXA; i++) {
        for (int j = 0; j < MAXBC; j++) {
            for (int k = 0; k < MAXBC; k++) {
                for (int l = 0; l < MAXT; l++) {
                    dp[i][j][k][l] = -1.0;
                }
            }
        }
    }
    printf("%.4lf\n", DP(n0-1, 0, 0, 0));
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        input();
        solve();
    }
    return 0;
}
