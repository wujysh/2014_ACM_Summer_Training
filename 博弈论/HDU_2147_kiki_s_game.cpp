#include <iostream>
#include <cstdio>
using namespace std;

int n, m;

void solve() {
    if (n % 2 == 1 && m % 2 == 1) {
        printf("What a pity!\n");
    } else {
        printf("Wonderful!\n");
    }
}

int main() {
    while (~scanf("%d%d", &n, &m) && (n || m)) {
        solve();
    }
    return 0;
}
