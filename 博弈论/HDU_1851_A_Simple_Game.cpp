#include <iostream>
#include <cstdio>
using namespace std;

int nCase, n, ans, m, l;

void solve() {
    ans = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &m, &l);
        ans ^= m % (l+1);
    }
    if (ans == 0) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        solve();
    }
    return 0;
}
