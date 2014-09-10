#include <algorithm>
//#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 10010;
int nCase, cnt, n, m, j, head, tail;
int s[MAXN], dp[MAXN][MAXN], q[MAXN];

int Q(int x, int y) {
    return dp[x][j-1] - dp[y][j-1] + s[x+1]*s[x+1] - s[y+1]*s[y+1];
}

int S(int x, int y) {
    return 2 * (s[x+1] - s[y+1]);
}

void init() {
    cnt++;
    memset(dp, 0, sizeof(dp));
}

void input() {
    scanf("%d%d", &n, &m);
    //cin >> n >> m;
    for (int i = 0; i < n; i++) {
        scanf("%d", &s[i]);
        //cin >> s[i];
    }
}

void work() {
    sort(s, s+n);
    for (int i = 0; i < n; i++) {
        dp[i][1] = (s[i] - s[0])*(s[i] - s[0]);
    }
    for (j = 2; j <= m; j++) {
        memset(q, 0, sizeof(q));
        head = tail = 0;
        q[tail++] = 0;

        for (int i = 1; i < n; i++) {
            while (head+1 < tail && Q(q[head+1], q[head]) <= s[i] * S(q[head+1], q[head])) {
                head++;
            }
            //dp[i][j] = min(dp[k][j-1] + (s[i] - s[k+1])^2);  (0 <= k < i)
            dp[i][j] = dp[q[head]][j-1] + (s[i] - s[q[head]+1])*(s[i] - s[q[head]+1]);

            while (head+1 < tail && Q(q[tail-2], q[tail-1]) * S(q[tail-1], i) >= Q(q[tail-1], i) * S(q[tail-2], q[tail-1])) {
                tail--;
            }
            q[tail++] = i;
        }
    }
}

void output() {
    printf("Case %d: %d\n", cnt, dp[n-1][m]);
    //cout << "Case " << cnt << ": " << dp[n-1][m] << endl;
}

int main() {
    //ios::sync_with_stdio(false);
    //cin >> nCase;
    scanf("%d", &nCase);
    while (nCase--) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
