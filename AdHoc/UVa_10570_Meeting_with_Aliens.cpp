#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 510;
const int INF = 0x3f3f3f3f;
int n, a[MAXN], b[MAXN];

void input() {
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }
}

void solve() {
    int ans1 = 0, ans2 = 0, ans = INF, cnt;

    for (int index_1 = 0; index_1 < n; index_1++) {
        cnt = 1;
        ans1 = 0;
        for (int i = index_1; cnt <= n; cnt++) {
            a[cnt] = b[i];
            i = (i + 1) % n;
        }
        for (int i = 1; i <= n; i++) {
            while (a[i] != i) {
                swap(a[i], a[a[i]]);
                ans1++;
            }
        }
        ans = min(ans, ans1);

        cnt = 1;
        ans2 = 0;
        for (int i = index_1; cnt <= n; cnt++) {
            a[cnt] = b[i];
            i = (i - 1 + n) % n;
        }
        for (int i = 1; i <= n; i++) {
            while (a[i] != i) {
                swap(a[i], a[a[i]]);
                ans2++;
            }
        }
        ans = min(ans, ans2);
    }

    printf("%d\n", ans);
}

int main() {
    while (~scanf("%d", &n) && n) {
        input();
        solve();
    }
    return 0;
}
