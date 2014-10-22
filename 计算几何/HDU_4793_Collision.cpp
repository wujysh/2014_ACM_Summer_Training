#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

double Rm, R, r, x, y, vx, vy;

void solve() {
    double x2 = x + vx, y2 = y + vy;
    if (x2*x2 + y2*y2 > x*x + y*y) {
        printf("0.000\n");
        return;
    }
    double d = abs(x*vy - y*vx) / sqrt(vx*vx + vy*vy);
    double l1 = 0.0, l2 = 0.0;
    if (d < R + r) {
        l1 = 2.0 * sqrt((R+r)*(R+r) - d*d);
    }
    if (d < Rm + r) {
        l2 = 2.0 * sqrt((Rm+r)*(Rm+r) - d*d);
    }
    double l = l1 - l2;
    double v = sqrt(vx*vx + vy*vy);
    printf("%.3f\n", l / v);
}

int main() {
    while (~scanf("%lf%lf%lf%lf%lf%lf%lf", &Rm, &R, &r, &x, &y, &vx, &vy)) {
        solve();
    }
    return 0;
}
