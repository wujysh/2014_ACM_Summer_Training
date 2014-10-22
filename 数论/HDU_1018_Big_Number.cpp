#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 4000010;
int n, nCase;
double ans, Log10[MAXN];

double calcLog10(int x) {
    if (x < MAXN) {
        if (Log10[x] > 0) return Log10[x];
        return Log10[x] = log10(x);
    } else {
        return log10(x);
    }
}

void init() {
    for (int i = 0; i < MAXN; i++) {
        Log10[i] = -1.0;
    }
}

void solve() {
    scanf("%d", &n);
    ans = 1.0;
    for (int i = 1; i <= n; i++) {
        ans += calcLog10(i);
    }
    printf("%d\n", (int)ans);
}

int main() {
    init();
    scanf("%d", &nCase);
    while (nCase--) {
        solve();
    }
    return 0;
}
