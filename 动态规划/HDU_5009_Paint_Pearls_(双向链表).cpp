#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>
using namespace std;

const int MAXN = 50010;
const int INF = 0x3f3f3f3f;

int a[MAXN], pre[MAXN], nxt[MAXN], dp[MAXN], n;
map<int, int> mp;

void init() {
    memset(dp, 0x3f, sizeof(dp));
    mp.clear();
    dp[0] = 0;
    pre[0] = -1;
}

void input() {
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        pre[i] = i - 1;
        nxt[i] = i + 1;
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        if (mp.find(a[i]) == mp.end()) {
            mp[a[i]] = i;
        } else {
            int id = mp[a[i]];
            nxt[pre[id]] = nxt[id];
            pre[nxt[id]] = pre[id];
            mp[a[i]] = i;
        }

        int cnt = 0;
        for (int j = pre[i]; j != -1; j = pre[j]) {
            cnt++;
            dp[i] = min(dp[i], dp[j] + cnt * cnt);
            if (cnt * cnt > i) break;
        }
    }

    printf("%d\n", dp[n]);
}

int main() {
    while (~scanf("%d", &n)) {
        init();
        input();
        solve();
    }
    return 0;
}
