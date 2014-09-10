#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 10010;
const int MAXP = 1300;
int prime[MAXP], totPrime, n, k, p, cnt, ans, fac[MAXP][MAXN], indexPrime;
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

void init() {
    getPrime(10000);
    for (int i = 1; i <= totPrime; i++) {
        fac[i][0] = 1;
        for (int j = 1; j < prime[i]; j++) {
            fac[i][j] = fac[i][j-1] * j % prime[i];
        }
    }
}

int pow_mod(int a, int b, int p) {
    int ans = 1, t = a;
    while (b) {
        if (b & 1) {
            ans = ans * t % p;
        }
        t = t * t % p;
        b = b >> 1;
    }
    return ans;
}

int C(int n, int m, int p) {
    //cout <<"C: "<< n << " " << m << " " << p << endl;
    if (n < m) return 0;
    int a = fac[indexPrime][n];
    int b = pow_mod(fac[indexPrime][m] * fac[indexPrime][n-m] % p, p-2, p) % p;
    return (a * b) % p;
}

int lucas(int n, int m, int p) {
    //cout <<"L: " << n << " " << m << " " << p << endl;
    if (n == 0 && m == 0) return 1;
    return (C(n%p, m%p, p) * lucas(n/p, m/p, p)) % p;
}

int main() {
    ios::sync_with_stdio(false);
    init();
    while (cin >> n >> k >> p) {
        if (k > n / 2) {
            k = n - k;
        }
        indexPrime = lower_bound(prime+1, prime+1+totPrime, p) - prime;
        ans = (lucas(n+1, k, p) + (n - k)) % p;
        cout << "Case #" << ++cnt << ": " << ans << endl;
    }
    return 0;
}
