#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const double eps = 1e-8;
int nCase, n, m, a, b;
double suma, sumb;

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        scanf("%d%d", &n, &m);
        n--;
        suma = sumb = 0.0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &a);
            suma += a;
        }
        for (int i = 0; i < m; i++) {
            scanf("%d", &b);
            sumb += b;
        }
        suma /= n;
        sumb /= m;
        printf("%d %d\n", (int)ceil(sumb+eps), (int)floor(suma-eps));


    }
    return 0;
}
