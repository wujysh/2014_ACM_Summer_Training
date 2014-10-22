#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 1000010;
int n;
double a[MAXN];

struct Node {
    int cnt;
    double base;
} b[MAXN];

void init() {
    for (int i = 0; i < MAXN; i++) {
        a[i] = -1.0;
    }

    a[1] = 0.5;
    b[1].base = 0.5;
    b[1].cnt = 0;

    for (int i = 2; i < MAXN; i++) {
        a[i] = a[i-1] + (1 - a[i-1]) * (1.0 / i) * (1.0 / (i + 1));

        b[i].base = b[i-1].base * (1.0 / i) * (1.0 / (i + 1));
        b[i].cnt = b[i-1].cnt;
        while (b[i].base < 0.1) {
            b[i].cnt++;
            b[i].base *= 10.0;
        }
    }
}

void solve() {
    printf("%.6lf ", a[n]);
    printf("%d\n", b[n].cnt);
}

int main() {
    init();
    while (~scanf("%d", &n)) {
        solve();
    }
    return 0;
}
