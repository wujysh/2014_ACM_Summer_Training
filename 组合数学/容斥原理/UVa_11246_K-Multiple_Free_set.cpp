#include <iostream>
#include <cstdio>
using namespace std;

int n, k, nCase;

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        scanf("%d%d", &n, &k);
        int ans = 0, flag = 1;
        while (n) {
            ans += flag * n;
            flag *= -1;
            n /= k;
        }
        printf("%d\n", ans);
    }
    return 0;
}
