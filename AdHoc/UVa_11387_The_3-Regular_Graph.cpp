#include <iostream>
#include <cstdio>
using namespace std;

int n;

void solve() {
    if (n < 4) {
        printf("Impossible\n");
    } else {
        if (n % 2 == 0) {
            printf("%d\n", n + n / 2);
            for (int i = 1; i <= n; i++) {
                if (i == n) {
                    printf("%d %d\n", n, 1);
                } else {
                    printf("%d %d\n", i, i+1);
                }
            }
            for (int i = 1; i <= n/2; i++) {
                printf("%d %d\n", i, i + n/2);
            }
        } else {
            printf("Impossible\n");
        }
    }
}

int main() {
    while (~scanf("%d", &n) && n) {
        solve();
    }
    return 0;
}
