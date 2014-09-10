#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 160;
const int INF = 0x3f3f3f3f;
int n, p, dp[MAXN][MAXN], root, ans;
bool isRoot[MAXN];
vector<int> child[MAXN];

void init() {
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < n; i++) {
        child[i].clear();
    }
    memset(isRoot, true, sizeof(isRoot));
    ans = INF;
}

void input() {
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        child[a].push_back(b);
        isRoot[b] = false;
    }
    for (int i = 1; i <= n; i++) {
        if (isRoot[i]) {
            root = i;
            break;
        }
    }
}

void dfs(int x) {
    for (int i = 0; i < child[x].size(); i++) {
        dfs(child[x][i]);
    }

    for (int s = 0; s < child[x].size(); s++) {
        for (int i = p; i >= 1; i--) {
            for (int j = 1; j <= i; j++) {
                dp[x][i] = min(dp[x][i-j] + dp[child[x][s]][j] - 2, dp[x][i]);
            }
        }
    }
}

void work() {
    for (int i = 0; i <= n; i++) {
        dp[i][1] = child[i].size() + 1;
    }
    dp[root][1] = child[root].size();

    dfs(root);

    for (int i = 1; i <= n; i++) {
        ans = min(ans, dp[i][p]);
    }
}

void output() {
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> p) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
