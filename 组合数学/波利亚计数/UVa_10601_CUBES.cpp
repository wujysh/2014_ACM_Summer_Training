#include <iostream>
#include <cstring>
using namespace std;

int nCase, a[7], b[7];
long long c[15][15];

void init() {
    for (int i = 0; i <= 12; i++) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; j++) {
            c[i][j] = c[i-1][j-1] + c[i-1][j];
        }
    }
}

void input() {
    memset(a, 0, sizeof(a));
    for (int i = 0; i < 12; i++) {
        int x;
        cin >> x;
        a[x-1]++;
    }
}

long long solve(int k) {
    int n = 0;
    for (int i = 0; i < 6; i++) {
        if (b[i] % k == 0) {
            b[i] /= k;
            n += b[i];
        } else {
            return 0;
        }
    }
    long long ans = 1;
    for (int i = 0; i < 6; i++) {
        ans *= c[n][b[i]];
        n -= b[i];
    }
    return ans;
}

long long still_polya() {
    memcpy(b, a, sizeof(a));
    return solve(1);
}

long long point_polya() {
    memcpy(b, a, sizeof(a));
    return 4 * 2 * solve(3);
}

long long plane_polya() {
    long long ans = 0;
    memcpy(b, a, sizeof(a));
    ans += 3 * 2 * solve(4);
    memcpy(b, a, sizeof(a));
    ans += 3 * 1 * solve(2);
    return ans;
}

long long edge_polya() {
    long long ans = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            memcpy(b, a, sizeof(a));
            b[i]--;  b[j]--;
            if (b[i] < 0 || b[j] < 0) continue;
            ans += 6 * solve(2);
        }
    }
    return ans;
}

long long polya() {
    return (still_polya() + point_polya() + plane_polya() + edge_polya()) / 24;
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
