#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 100010;
int minDiv[MAXN], phi[MAXN], sum[MAXN], factorA[MAXN], factorB[MAXN], totFactor, prime[MAXN], totPrime, nCase, a, b, c, d, k, cnt;
long long ans;
bool isPrime[MAXN];

void getPrime(int n) {
    memset(isPrime, true, sizeof(isPrime));
    totPrime = 0;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            prime[++totPrime] = i;
        }
        for (int j = 1; j <= totPrime && i*prime[j] <= n; j++) {
            isPrime[i*prime[j]] = false;
            if (i % prime[j] == 0) break;
        }
    }
}

void getFactor(int n) {
    totFactor = 0;
    int now = n;
    for (int i = 1; i <= totPrime && prime[i]*prime[i] <= now; i++) {
        if (now % prime[i] == 0) {
            factorA[++totFactor] = prime[i];
            factorB[totFactor] = 0;
            while (now % prime[i] == 0) {
                factorB[totFactor]++;
                now /= prime[i];
            }
        }
    }
    if (now != 1) {
        factorA[++totFactor] = now;
        factorB[totFactor] = 1;
    }
}

void genPhi() {
    for (int i = 1; i < MAXN; i++) {
        minDiv[i] = i;
    }
    for (int i = 2; i*i < MAXN; i++) {
        if (minDiv[i] == i) {
            for (int j = i*i; j < MAXN; j += i) {
                minDiv[j] = i;
            }
        }
    }
    phi[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        phi[i] = phi[i / minDiv[i]];
        if ((i / minDiv[i]) % minDiv[i] == 0) {
            phi[i] *= minDiv[i];
        } else {
            phi[i] *= minDiv[i] - 1;
        }
    }
}

void init() {
    ans = 0;
}

void solve() {
    cin >> a >> b >> c >> d >> k;
    a = c = 1;
    if (k == 0 || k > b || k > d) {
        ans = 0;
        return;
    }
    b /= k;
    d /= k;
    if (b < d) swap(b, d);

    for (int i = 1; i <= d; i++) {
        ans += phi[i];
    }
    for (int i = d+1; i <= b; i++) {
        ans += d;
        getFactor(i);
        for (int j = 1; j < (1 << totFactor); j++) {
            int cnt = 0, x = 1;
            for (int k = 1; k <= totFactor; k++) {
                if (j & (1 << (k-1))) {
                    cnt++;
                    x = x * factorA[k];
                }
            }
            if (cnt & 1) {
                ans -= d / x;
            } else {
                ans += d / x;
            }
        }
    }
}

void output() {
    cout << "Case " << ++cnt << ": " << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    getPrime(400);
    genPhi();
    cin >> nCase;
    while (nCase--) {
        init();
        solve();
        output();
    }
    return 0;
}
