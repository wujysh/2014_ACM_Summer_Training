#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

int n, S, xx1, yy1, xx2, yy2;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d%d", &xx1, &yy1, &xx2, &yy2);
        if (xx1 > xx2) {
            swap(xx1, xx2);
            swap(yy1, yy2);
        }
        S = max(max(xx1, yy1), max(xx2, yy2));
        if (xx2 - xx1 == 0) {
            printf("Case %d: 0 0 1 0\n", i);
        } else if (yy2 - yy1 == 0) {
            printf("Case %d: 0 0 0 1\n", i);
        } else {
            if (yy2 - yy1 > 0) {
                printf("Case %d: %d %d %d %d\n", i, 0, S, (yy2 - yy1), S - (xx2 - xx1));
            } else {
                printf("Case %d: %d %d %d %d\n", i, 0, 0, yy1 - yy2, xx2 - xx1);
            }
        }
    }
    return 0;
}
