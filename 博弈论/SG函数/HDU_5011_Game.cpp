#include <iostream>
#include <cstdio>
using namespace std;

int n, a, ans;

int main() {
    while (~scanf("%d", &n)) {
        ans = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &a);
            ans ^= a;
        }
        if (ans == 0) {
            printf("Lose\n");
        } else {
            printf("Win\n");
        }
    }
    return 0;
}
