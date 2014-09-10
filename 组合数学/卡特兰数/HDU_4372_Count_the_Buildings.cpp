#include <cstdio>
using namespace std;

const int MAXN = 2010;
const int MOD = 1000000007;
int N, F, B, nCase;
long long c[MAXN][MAXN], s[MAXN][MAXN];

inline void init() {
    for (int i = 1; i < MAXN; i++) {
        c[i][0] = c[i][i] = 1;
        s[i][0] = 0;  s[i][i] = 1;
        for (int j = 1; j < i; j++) {
            c[i][j] = (c[i-1][j-1] + c[i-1][j]) % MOD;
            s[i][j] = (s[i-1][j-1] + (i-1)*s[i-1][j]) % MOD;
        }
    }
}

int main() {
    init();
    scanf("%d", &nCase);
    while (nCase--) {
        scanf("%d%d%d", &N, &F, &B);
        if (F+B > N+1) {
            printf("0\n");
        } else {
            printf("%d\n", (c[F+B-2][F-1] * s[N-1][F+B-2]) % MOD);
        }
    }
    return 0;
}
