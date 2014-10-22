#include <iostream>
#include <cstdio>
using namespace std;

int m, k, ans;

int main() {
    while (~scanf("%d", &m) && m) {
        ans = 0;
        for (int i = 0; i < m; i++) {
            scanf("%d", &k);
            ans ^= k;
        }
        if (ans == 0) {
            printf("Grass Win!\n");
        } else {
            printf("Rabbit Win!\n");
        }
    }
    return 0;
}
