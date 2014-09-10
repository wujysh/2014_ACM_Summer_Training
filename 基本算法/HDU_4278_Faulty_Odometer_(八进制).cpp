#include <iostream>
#include <cmath>
using namespace std;

int n;
int a[10] = {0, 1, 2, 0, 3, 4, 5, 6, 0 ,7}, sum;

void solve() {
    sum = 0;
    int k = 1;
    while (n > 0) {
        int x = n % 10;
        n /= 10;
        sum += a[x] * k;
        k *= 8;
    }
    printf("%d\n", sum);
}

int main() {
    while (~scanf("%d", &n) && n) {
        printf("%d: ", n);
        solve();
    }
    return 0;
}
