#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 3000010;
long long N, factorA[MAXN], factorB[MAXN], totFactor, prime[MAXN], totPrime, ans;
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

void getFactor(long long n) {
    totFactor = 0;
    long long now = n;
    for (int i = 1; i <= totPrime && prime[i] <= now; i++) {
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

void solve() {
    while (N & 1 ==0 ) N >>= 1;
    getFactor(N);
    ans = 1;
    for (int i = 1; i <= totFactor; i++) {
        if (factorA[i] & 1 == 1) {
            ans *= factorB[i] + 1;
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    getPrime(3000000);
    while (cin >> N) {
        solve();
    }
    return 0;
}
