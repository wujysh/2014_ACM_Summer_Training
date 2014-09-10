#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int MAXN = 15;
int N, mine[MAXN];
double p, ans;

struct Matrix {
    int n, m;
    double a[2][2];
    Matrix() : n(2), m(2) {
        memset(a, 0, sizeof(a));
    }
    Matrix operator*(const Matrix &b) const {
        Matrix tmp;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < b.m; j++) {
                for (int k = 0; k < m; k++) {
                    tmp.a[i][j] += a[i][k] * b.a[k][j];
                }
            }
        }
        return tmp;
    }
};

Matrix fast_pow(int i) {
    Matrix a, tmp;
    a.a[0][0] = p;    a.a[0][1] = 1 - p;
    a.a[1][0] = 1.0;  a.a[1][1] = 0.0;
    tmp.a[0][0] = 1;  tmp.a[1][1] = 1;
    while (i) {
        if (i & 1) {
            tmp = tmp * a;
        }
        a = a * a;
        i >>= 1;
    }
    return tmp;
}

void init() {
    ans = 1.0;
    memset(mine, 0, sizeof(mine));
    mine[0] = 0;  // guard
}

void input() {
    for (int i = 1; i <= N; i++) {
        cin >> mine[i];
    }
}

void work() {
    sort(mine, mine+N+1);
    bool flag = false;
    for (int i = 1; i <= N; i++) {
        if (mine[i] == mine[i-1] + 1) {
            flag = true;
            break;
        }
    }
    if (mine[0] == 1 || flag) {
        ans = 0.0;
        return;
    }

    for (int i = 1; i <= N; i++) {
        Matrix a = fast_pow(mine[i] - mine[i-1] - 1);
        ans *= 1 - a.a[0][0];
    }
}

void output() {
    cout << fixed << setprecision(7) << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> N >> p) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
