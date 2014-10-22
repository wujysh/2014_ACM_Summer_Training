#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

const double eps = 1e-6;
const double INF = 100000;
const int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
const int dy[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
double a, b, c, d, e, f, ans;

inline double calcZ(double x, double y) {
    double aa = c;
    double bb = d * y + e * x;
    double cc = a * x*x + b * y*y + f * x * y - 1;
    double delta = bb*bb - 4.0 * aa * cc;
    if (delta < 0) return INF;
    double z1 = (-1.0*bb + sqrt(delta)) / (2 * aa);
    double z2 = (-1.0*bb - sqrt(delta)) / (2 * aa);
    if (fabs(z1) < fabs(z2)) {
        return z1;
    } else {
        return z2;
    }
}

inline double dis(double x, double y, double z) {
    return sqrt(x*x + y*y + z*z);
}

void solve() {
    double x = 0, y = 0, z = calcZ(x, y), step = 10000, d = 0.5;
    while (step > eps) {
        for (int i = 0; i < 8; i++) {
            double nx = x + dx[i]*step;
            double ny = y + dy[i]*step;
            double nz = calcZ(nx, ny);
            if (nz > INF-1) continue;
            if (dis(nx, ny, nz) < dis(x, y, z)) {
                x = nx;  y = ny;  z = nz;
            }
        }
        step *= d;
    }

    printf("%.7lf\n", dis(x, y, z));
    //ans = min(ans, dis(x, y, z));
}
/*
void solve1(){
    ans=1e18;
    //get_point(0,0);
    //for(int i=0;i<10;i++) solve((rand()%10)*1.0/10/sqrt(a),(rand()%10)*1.0/10/sqrt(b));
    //for(int i=0;i<10;i++) solve((rand()%10)*1.0/10/sqrt(a),-(rand()%10)*1.0/10/sqrt(b));
    //for(int i=0;i<10;i++) solve(-(rand()%10)*1.0/10/sqrt(a),(rand()%10)*1.0/10/sqrt(b));
    //for(int i=0;i<10;i++) solve(-(rand()%10)*1.0/10/sqrt(a),-(rand()%10)*1.0/10/sqrt(b));
    printf("%.7f\n", ans);
}
*/
int main() {
    while (~scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &e, &f)) {
        solve();
    }
    return 0;
}
