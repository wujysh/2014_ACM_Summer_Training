#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 110;
int nCase, n;
char b[10];
double ans, p[MAXN];

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        scanf("%d %s", &n, &b);
        for (int i = 0; i < n; i++) {
            scanf("%lf", &p[i]);
            p[i] /= 100;
        }

        ans = 0;
        if (strcmp(b, "bit") == 0) {
            for (int i = 0; i < n; i++) {
                if (p[i] > 0)
                    ans += p[i] * log2(p[i]);
            }
        }
        if (strcmp(b, "nat") == 0) {
            for (int i = 0; i < n; i++) {
                if (p[i] > 0)
                    ans += p[i] * log(p[i]);
            }
        }
        if (strcmp(b, "dit") == 0) {
            for (int i = 0; i < n; i++) {
                if (p[i] > 0)
                    ans += p[i] * log10(p[i]);
            }
        }
        printf("%.12lf\n", -1.0 * ans);
    }
    return 0;
}
