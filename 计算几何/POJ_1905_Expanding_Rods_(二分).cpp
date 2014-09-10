#include <cstdio>
#include <cmath>
using namespace std;

const int eps = 1e-8;
double L, n, C;

int main() {
    while (~scanf("%lf%lf%lf", &L, &n, &C) && !(L<0 && n<0 && C<0)) {
        double LL = (1 + n*C) * L;
        double l = 0, r = L/2, Xmid;
        while (r - l > eps) {
            Xmid = (l + r) / 2;
            double R = (4*Xmid*Xmid + L*L) / (8*Xmid);
            double Lmid = 2 * R * asin(L / (2*R));
            if (Lmid - LL == 0) break;
            if (Lmid - LL < eps) {
                l = Xmid;
            } else {
                r = Xmid;
            }
        }
        printf("%.3f\n", Xmid);
    }
    return 0;
}
