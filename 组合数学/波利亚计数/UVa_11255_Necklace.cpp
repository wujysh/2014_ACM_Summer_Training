#include <iostream>
#include <cstring>
using namespace std;

int nCase, a[3], b[3], n;
long long c[45][45];

void init() {
    for (int i = 0; i <= 40; i++) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; j++) {
            c[i][j] = c[i-1][j-1] + c[i-1][j];
        }
    }
}

void input() {
    for (int i = 0; i < 3; i++) {
        cin >> a[i];
    }
    n = a[0] + a[1] + a[2];
}

long long solve(int k) {
    int n = 0;
    for (int i = 0; i < 3; i++) {
        if (b[i] % k == 0) {
            b[i] /= k;
            n += b[i];
        } else {
            return 0;
        }
    }
    long long ans = 1;
    for (int i = 0; i < 3; i++) {
        ans *= c[n][b[i]];
        n -= b[i];
    }
    return ans;
}

int gcd(int a, int b) {
    return (b == 0) ? a : gcd(b, a%b);
}

long long rotate_polya() {
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        memcpy(b, a, sizeof(a));
        ans += solve(n / gcd(i, n));
    }
    return ans;

}

long long flip_polya() {
    long long ans = 0;
    if (n % 2 == 0) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                memcpy(b, a, sizeof(a));
                b[i]--;  b[j]--;
                if (b[i] < 0 || b[j] < 0) continue;
                ans += (n / 2) * solve(2);
            }
        }
        memcpy(b, a, sizeof(a));
        ans += (n / 2) * solve(2);

    } else {
        for (int i = 0; i < 3; i++) {
            memcpy(b, a, sizeof(a));
            b[i]--;
            if (b[i] < 0) continue;
            ans += n * solve(2);
        }
    }
    return ans;

}

long long polya() {
    return (rotate_polya() + flip_polya()) / (2*n);
}

int main() {
    ios::sync_with_stdio(false);
    init();
    cin >> nCase;
    while (nCase--) {
        input();
        cout << polya() << endl;
    }
    return 0;
}
