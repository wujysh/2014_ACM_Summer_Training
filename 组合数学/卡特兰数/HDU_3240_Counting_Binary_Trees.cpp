#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 100010;
int n, m, prime[MAXN], cnt, num[MAXN];

int extend_gcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    } else {
        int r = extend_gcd(b, a % b, y, x);
        y -= x * (a / b);
        return r;
    }
}

void init() {
    cnt = 0;
    int t = m;
    for (int i = 2; i * i <= t; i++) {
        if (t % i == 0) {
            prime[cnt++] = i;
            while (t % i == 0) {
                t /= i;
            }
        }
    }
    if (t > 1) {
        prime[cnt++] = t;
    }
    memset(num, 0, sizeof(num));
}

void calcFZ(long long &ans, int x) {
    for (int i = 0; i < cnt; i++) {
        while (x % prime[i] == 0) {
            num[i]++;
            x /= prime[i];
        }
    }
    ans = (ans * x) % m;
}

void calcFM(long long &ans, int x) {
    for (int i = 0; i < cnt; i++) {
        while (x % prime[i] == 0 && num[i]) {
            num[i]--;
            x /= prime[i];
        }
    }
    if (x > 1) {
        int fm_ni, tmp;
        extend_gcd(x, m, fm_ni, tmp);
        ans = (ans * (((fm_ni % m) + m) % m)) % m;
    }
}

void solve() {
    long long ans = 1, res = 1, tmp;
    for (int i = 2; i <= n; i++) {
        calcFZ(ans, 4 * i - 2);
        calcFM(ans, i + 1);
        tmp = ans;
        for (int j = 0; j < cnt; j++) {
            for (int k = 0; k < num[j]; k++) {
                tmp = (tmp * prime[j]) % m;
            }
        }
        res = (res + tmp) % m;
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> m && (n || m)) {
        init();
        solve();
    }
    return 0;
}
