#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 10010;
struct Interval {
    int a, b;
    bool operator<(const Interval &p) const {
        return b < p.b;
    }
} interval[MAXN];
int ans, n;

void input() {
    for (int i = 0; i < n; i++) {
        cin >> interval[i].a >> interval[i].b;
    }
}

void solve() {
    sort(interval, interval+n);
    int x1 = interval[0].b, x2 = x1-1;
    ans = 2;
    for (int i = 1; i < n; i++) {
        if (!(interval[i].a <= x1 && x1 <= interval[i].b)) {
            x1 = interval[i].b;
            x2 = x1 - 1;
            ans += 2;
        } else {
            if (!(interval[i].a <= x2 && x2 <= interval[i].b)) {
                x2 = x1;
                x1 = interval[i].b;
                ans += 1;
            }
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n) {
        input();
        solve();
    }
    return 0;
}
