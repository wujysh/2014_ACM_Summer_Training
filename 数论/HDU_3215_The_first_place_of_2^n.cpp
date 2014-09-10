#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

const int MAXN = 10010;
const double eps = 1e-10;
int first[MAXN], cnt[10], n;

void init() {
    for (int i = 0; i <= 10000; i++) {
        first[i] = int(pow(10, i * log10(2.0) - int(i * log10(2.0))) + eps);
    }
}

void solve() {
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i <= n; i++) {
        cnt[first[i]]++;
    }
    for (int i = 1; i <= 9; i++) {
        if (i > 1) cout << " ";
        cout << cnt[i];
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    init();
    while (cin >> n && n != -1) {
        solve();
    }
    return 0;
}
