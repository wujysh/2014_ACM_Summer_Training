#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 10000010;
int prime[MAXN], tot, n;
bool isPrime[MAXN];

void getPrime(int n) {
    memset(isPrime, true, sizeof(isPrime));
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            tot++;
            prime[tot] = i;
        }
        for (int j = 1; j <= tot && i*prime[j] <= n; j++) {
            isPrime[i*prime[j]] = false;
            if (i % prime[j] == 0) break;
        }
    }
}

void solve() {
    if (n < 8) {
        cout << "Impossible." << endl;
    } else {
        if (n & 1) {
            cout << "2 3";
            for (int i = 0; i <= tot; i++) {
                int rest = n - 2 - 3 - prime[i];
                if (isPrime[rest]) {
                    cout << " " << prime[i] << " " << rest << endl;
                    break;
                }
            }
        } else {
            cout << "2 2";
            for (int i = 0; i <= tot; i++) {
                int rest = n - 2 - 2 - prime[i];
                if (isPrime[rest]) {
                    cout << " " << prime[i] << " " << rest << endl;
                    break;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    getPrime(10000000);
    while (cin >> n) {
        solve();
    }
    return 0;
}
