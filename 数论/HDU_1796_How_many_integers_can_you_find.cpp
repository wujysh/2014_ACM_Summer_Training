#include <iostream>
#include <vector>
using namespace std;

vector<int> a;
int n, m;
long long ans;

long long gcd(long long x, long long y) {
    return y > 0 ? gcd(y, x % y) : x;
}

long long lcm(long long x, long long y) {
    return x * y / gcd(x, y);
}

void init() {
    a.clear();
    ans = 0;
}

void input() {
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        if (x > 0) {
            a.push_back(x);
        }
    }
    m = a.size();
}

void work() {
    for (int i = 1; i < (1 << m); i++) {
        long long x = 1;
        int cnt = 0;
        for (int j = 0; j < m; j++) {
            if (i & (1 << j)) {
                cnt++;
                x = lcm(x, a[j]);
            }
        }
        if (cnt & 1) {
            ans += (n - 1) / x;
        } else {
            ans -= (n - 1) / x;
        }
    }
}

void output() {
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> m) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
