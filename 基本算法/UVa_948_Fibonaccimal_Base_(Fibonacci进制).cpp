#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 50;
int n, fib[MAXN], nCase;

void init() {
    fib[0] = 1;  fib[1] = 2;
    for (int i = 2; i < MAXN; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
}

void solve() {
    int a;
    scanf("%d", &a);

    printf("%d = ", a);

    bool flag = false;
    for (int i = 38; i >= 0; i--) {
        if (a >= fib[i]) {
            flag = true;
            printf("1");
            a -= fib[i];
        } else if (flag) {
            printf("0");
        }
    }
    printf(" (fib)\n");
}

int main() {
    init();
    scanf("%d", &nCase);
    while (nCase--) {
        solve();
    }
    return 0;
}
