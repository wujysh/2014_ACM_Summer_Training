#include <cstdio>
#include <cmath>
using namespace std;

const double INF = 1e+9;
const double eps = 1e-9;
double X1, Y1, X2, Y2, Lx, Ly, vD, vB, L;

int main() {
    while (~scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf", &X1, &Y1, &X2, &Y2, &Lx, &Ly, &vD, &vB, &L) && (X1 || Y1 || X2 || Y2 || Lx || Ly || vD || vB || L)) {
        double tB = L / vB;
        X1 += tB * Lx; Y1 += tB * Ly;
        double l = 0, r = INF;
        while (l + eps < r) {
            double mid = (l + r) / 2;
            double x = X1 + mid*Lx, y = Y1 + mid*Ly;
            double d = sqrt((x-X2)*(x-X2) + (y-Y2)*(y-Y2));
            double dD = vD * mid;
            if (d <= L) {
                if (d + dD >= L) {
                    r = mid;
                } else {
                    l = mid;
                }
            } else {
                if (d - dD <= L) {
                    r = mid;
                } else {
                    l = mid;
                }
            }
        }
        printf("%.3lf %.3lf\n", L, l+tB);
    }
    return 0;
}
