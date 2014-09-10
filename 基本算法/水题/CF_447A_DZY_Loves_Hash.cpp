#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 3100;
int n, p;
bool bucket[MAXN];

void init() {
    memset(bucket, false, sizeof(bucket));
}

void solve() {
    bool flag = true;
    for (int i = 1; i <= n; i++) {
        int x, h;
        cin >> x;
        h = x % p;
        if (flag) {
            if (bucket[h]) {
                cout << i << endl;
                flag = false;
            } else {
                bucket[h] = true;
            }
        }
    }
    if (flag) cout << -1 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> p >> n) {
        init();
        solve();
    }
    return 0;
}
