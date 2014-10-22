#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

const int MAXN = 200010;
int a[MAXN], n, m, l, nCase, cnt;

void input() {
    scanf("%d%d%d", &n, &m, &l);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    a[n+1] = m;
}

void solve() {
    sort(a, a+n+2);

    int cur = 0, pre = -l, ans = 0, i = 0;
    while (cur < m) {
        while (i < n+2 && a[i] <= cur + l) i++;
        if (a[i-1] > cur && a[i-1] <= cur + l) {  // jump directly
            pre = cur;
            cur = a[i-1];
            ans++;
        } else {  // need help
            int t = (a[i] - cur) / (l + 1) - 1;
            int tmp = max(pre + l + 1, cur + 1);
            if (t) {
                pre = tmp + (t - 1) * (l + 1);
                cur += t * (l + 1);
                ans += 2 * t;
            } else {
                pre = cur;
                cur = tmp;
                ans++;
            }
        }
    }

    printf("Case #%d: %d\n", ++cnt, ans);
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        input();
        solve();
    }
    return 0;
}
