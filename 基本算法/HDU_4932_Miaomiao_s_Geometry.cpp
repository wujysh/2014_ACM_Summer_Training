#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int INF = 1e10;
int nCase, n;
double ans, a[MAXN];

bool check(double d) {
    double pre = a[0];
    for (int i = 1; i < n-1; i++) {
        if (pre == a[i]) {
            continue;
        }
        if (pre + d <= a[i]) {
            pre = a[i];
        } else {
            if (a[i] + d > a[i+1]) {
                return false;
            } else {
                pre = a[i] + d;
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a, a+n);
        ans = 0.0;
        for (int i = 0; i < n-1; i++) {
            if (check(a[i+1] - a[i])) {
                ans = max(ans, a[i+1] - a[i]);
            }
            if (check((a[i+1] - a[i]) / 2)) {
                ans = max(ans, (a[i+1] - a[i]) / 2);
            }
        }
        cout << fixed << setprecision(3) << ans << endl;
    }
    return 0;
}
