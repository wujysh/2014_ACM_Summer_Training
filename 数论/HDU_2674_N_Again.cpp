#include <iostream>
using namespace std;

const int MAXN = 50;
int n, ans[MAXN];

void init() {
    ans[0] = ans[1] = 1;
    for (int i = 2; i < 41; i++) {
        ans[i] = (ans[i-1] * i) % 2009;
    }
}

void solve() {
    if (n >= 41) {
        cout << 0 << endl;
    } else {
        cout << ans[n] << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    init();
    while (cin >> n) {
        solve();
    }
    return 0;
}
