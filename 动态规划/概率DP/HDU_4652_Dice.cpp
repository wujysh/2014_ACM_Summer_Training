#include <cstdio>
#include <cmath>
using namespace std;

int T, q;
double m, n, ans, tmp;

int main() {
    while (scanf("%d", &T) == 1) {
        for (int i = 0; i < T; i++) {
            scanf("%d%lf%lf", &q, &m, &n);

            if (q == 0) {
                ans = (pow(m, n) - 1.0) / (m - 1.0);

            } else if (q == 1) {
                ans = 0;  tmp = 1;
                for (int j = 1; j <= n; j++) {
                    ans += tmp;
                    tmp *= m / (m - j);
                }
            }

            printf("%.9lf\n", ans);
        }
    }
    return 0;
}
