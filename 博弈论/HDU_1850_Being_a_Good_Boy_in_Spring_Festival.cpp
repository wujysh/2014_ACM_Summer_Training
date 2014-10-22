#include <iostream>
#include <cstdio>
using namespace std;

const int MAXM = 110;
int m, n[MAXM], ans, sum;

int main() {
    while (~scanf("%d", &m) && m) {
        ans = 0;
        for (int i = 0; i < m; i++) {
            scanf("%d", &n[i]);
            ans ^= n[i];
        }
        sum = 0;
        for (int i = 0; i < m; i++) {
            if ((n[i] ^ ans) < n[i]) {
                sum++;
            }
        }
        printf("%d\n", sum);
    }
    return 0;
}

/*
记 n[1] ^ n[2] ^ n[3] ^ ... ^ n[m] = x
1. 当 x == 0，该局势为必败态;
2. 当 x != 0，该局势为必胜态,
    如果把 n[i] 变成 x ^ n[i]，
    则 n[1] ^ ... ^ n[i-1] ^ (x^n[i]) ^ n[i+1] ^ ... ^ n[m] = 0，该局势为必败态,
    所以，如果 n[i] > x ^ n[i]，即能将 n[i] 变为 x^n[i] 张，给对方必败态。
*/
