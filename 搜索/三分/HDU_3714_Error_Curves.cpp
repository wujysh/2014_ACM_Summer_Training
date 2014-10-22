#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 10010;
const int INF = 1e+10;
const double eps = 1e-10;

int nCase, n;
struct Func {
    double a, b, c;
} func[MAXN];

void input() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf%lf%lf", &func[i].a, &func[i].b, &func[i].c);
    }
}

double calc(double x) {
    double ret = -1.0 * INF;
    for (int i = 0; i < n; i++) {
        double f = func[i].a * x * x + func[i].b * x + func[i].c;
        if (f > ret) {
            ret = f;
        }
    }
    return ret;
}

void solve() {
    double l = 0.0, r = 1000.0;
    while (r - l > eps) {
        double ml = (l + r) / 2.0;
        double mr = (ml + r) / 2.0;
        if (calc(ml) > calc(mr)) {
            l = ml;
        } else {
            r = mr;
        }
    }
    printf("%.4lf\n", calc(l));
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        input();
        solve();
    }
    return 0;
}
