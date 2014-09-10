#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 100010;
long long bit[MAXN], ans;
vector<int> a, b;
int n, k;

long long sum(int i) {
    long long s = 0;
    while (i > 0) {
        s += bit[i];
        i -= i & (-i);
    }
    return s;
}

void add(int i, int x) {
    while (i <= b.size()) {
        bit[i] += x;
        i += i & (-i);
    }
}

void init() {
    memset(bit, 0, sizeof(bit));
    a.resize(n);
    ans = 0;
}

void solve() {
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());

    for (int i = 0; i < n; i++) {
        int x = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
        ans += i - sum(x+1);
        add(x+1, 1);
    }
    cout << max(ans-k, 0LL) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> k) {
        init();
        solve();
    }
    return 0;
}
