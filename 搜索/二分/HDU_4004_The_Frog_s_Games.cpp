#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int INF = 1000000010;
const int MAXN = 500010;

int a[MAXN], n, m, L;

int main() {
    while (scanf("%d %d %d", &L, &n, &m) != EOF) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        sort(a, a + n);

        int Min = a[0];
        for (int i = 1; i < n; i++) {
            Min = max(Min, a[i] - a[i - 1]);
        }
        Min = max(L - a[n - 1], Min);
        if (m == n + 1) {
            printf("%d\n", Min);
            continue;
        }

        int l = 0, r = L, ans = INF;
        a[n] = INF;
        while (l <= r) {
            int cnt = 0, mid = (l + r) >> 1, e = 0, flag = -1;
            int p = mid;
            while (true) {
                if (p >= L) {
                    cnt++;
                    break;
                }
                int t = upper_bound(a, a + n + 1, p) - a - 1;
                if (flag == t) {
                    cnt = INF;
                    break;
                }
                e = a[t], cnt++, flag = t;
                p = e + mid;
                if (cnt > m) break;
            }
            if (cnt <= m) {
                ans = min(mid, ans);
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}
