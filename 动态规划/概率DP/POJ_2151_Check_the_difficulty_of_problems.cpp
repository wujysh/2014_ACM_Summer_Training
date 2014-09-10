//#include <iostream>
//#include <iomanip>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXT = 1010, MAXM = 45;
int M, T, N;
double P[MAXT][MAXM], PP[MAXT][MAXM], ans;

void init() {
    memset(PP, 0, sizeof(PP));
}

void input() {
    for (int i = 1; i <= T; i++) {
        for (int j = 1; j <= M; j++) {
            scanf("%lf", &P[i][j]);
            //cin >> P[i][j];
        }
    }
}

void work() {
    for (int i = 1; i <= T; i++) {
        PP[i][0] = 1.0 - P[i][1];
        PP[i][1] = P[i][1];
        for (int j = 2; j <= M; j++) {
            double tmp[MAXM];
            memset(tmp, 0, sizeof(tmp));
            for (int k = 0; k <= j-1; k++) {
                tmp[k] = (1.0 - P[i][j]) * PP[i][k];
            }
            for (int k = 1; k <= j; k++) {
                tmp[k] += P[i][j] * PP[i][k-1];
            }
            memcpy(PP[i], tmp, sizeof(tmp));
        }
    }

    double Pa = 1.0, Pb = 1.0;
    for (int i = 1; i <= T; i++) {
        Pa *= 1.0 - PP[i][0];

        double tmp = 0.0;
        for (int j = 1; j <= N-1; j++) {
            tmp += PP[i][j];
        }
        if (PP[i][0] == 1) {
            tmp = 1.0;
        } else {
            tmp /= 1.0 - PP[i][0];
        }
        Pb *= tmp;
    }
    Pb = 1.0 - Pb;
    ans = Pa * Pb;
}

void output() {
    printf("%.3f\n", ans);
    //cout << fixed << setprecision(3) << ans << endl;
}

int main() {
    //ios::sync_with_stdio(false);
    //while (cin >> M >> T >> N && (M || T || N)) {
    while (scanf("%d%d%d", &M, &T, &N) == 3 && (M || T || N)) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
