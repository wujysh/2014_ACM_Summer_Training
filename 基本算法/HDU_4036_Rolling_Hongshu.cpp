#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

const double G = 40.0;
const int MAXN = 1010;
int nCase, cnt = 0, N, M;
double x[MAXN], h[MAXN], p[MAXN], v[MAXN], m[MAXN], w, ans, v1, v2, hh;

void init() {
    ans = 0;
}

void solve() {
    scanf("%d%d%lf", &N, &M, &w);
    scanf("%lf%lf", &x[0], &h[0]);
    for (int i = 1; i < N; i++) {
        scanf("%lf%lf", &x[i], &h[i]);
        x[i] += x[0];
        if (h[i] < h[0]) {
            v1 = 0;
        } else {
            v1 = sqrt(G*(h[i] - h[0]));
        }
        ans = max(ans, v1);
    }
    for (int i = 0; i < M; i++) {
        scanf("%lf%lf%lf", &p[i], &v[i], &m[i]);
        p[i] += x[0];
        for (int j = 0; j < N-1; j++) {
            if (p[i] >= x[j] && p[i] <= x[j+1]) {
                hh = h[j] + (h[j+1] - h[j])*(p[i] - x[j])/(x[j+1]-x[j]);
                break;
            }
        }
        v2 = sqrt(G*(hh-h[0]) + v[i]*v[i]);
        ans = max(ans, v2);
    }
    printf("Case %d: %.2lf\n", ++cnt, ans);
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        init();
        solve();
    }
    return 0;
}
