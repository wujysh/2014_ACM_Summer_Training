#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

int st[10][10], tmp[10][10], T;
bool vis[10][10][10][10];
int sx, sy, ex, ey;
int sx1, sy1, ex1, ey1;
struct node {
    int x1, y1, x2, y2;
    string ans;
    node(int x1, int y1, int x2, int y2, string ans): x1(x1), y1(y1), x2(x2), y2(y2), ans(ans) {}
};
int d[4][2] = {1, 0, 0, -1, 0, 1, -1, 0};
char s[4] = {'D', 'L', 'R', 'U'};
int f[4] = {2, 1, 4, 8};
vector<string> ans;

bool cmp(string a, string b) {
    if (a.size() == b.size()) {
        return a < b;
    }
    return a.size() < b.size();
}
void solve() {
    if (sx == ex && sy == ey && sx1 == ex1 && sy1 == ey1) {
        printf("\n");
        return;
    }
    ans.clear();
    queue<node> q;
    //cout<<sx<<" "<<sy<<" "<<sx1<<" "<<sy1<<endl;
    q.push(node(sx, sy, sx1, sy1, ""));
    memset(vis, 0, sizeof vis);
    vis[sx][sy][sx1][sy1] = 1;
    string ret = "";
    while (!q.empty()) {
        node now = q.front();
        q.pop();
        if (now.x1 == ex && now.y1 == ey && now.x2 == ex1 && now.y2 == ey1) {
            ans.push_back(now.ans);
        }
        int x1, y1, x2, y2;
        for (int i = 0; i < 4; i++) {
            x1 = now.x1 + d[i][0];
            y1 = now.y1 + d[i][1];
            x2 = now.x2 + d[i][0];
            y2 = now.y2 + d[i][1];
            if (st[now.x1][now.y1]&f[i]) {
                x1 = now.x1, y1 = now.y1;
            }
            if (tmp[now.x2][now.y2]&f[i]) {
                x2 = now.x2, y2 = now.y2;
            }
            if (!(x1 >= 1 && x1 <= 6 && y1 >= 1 && y1 <= 6 && x2 >= 1 && x2 <= 6 && y2 >= 1 && y2 <= 6)) continue;
            if (!(st[x1][y1] & (1 << 4)) || !(tmp[x2][y2] & (1 << 4))) continue;
            if (!vis[x1][y1][x2][y2]) {
                vis[x1][y1][x2][y2] = 1;
                q.push(node(x1, y1, x2, y2, now.ans + s[i]));
            }
        }
    }
    if (ans.empty()) {
        printf("-1\n");
    } else {
        printf("%s\n", ans[0].c_str());
    }
}

int main() {
    scanf("%d", &T);
    for (int i = 1; i <= 6; i++)
        for (int j = 1; j <= 6; j++) {
            scanf("%d", &st[i][j]);
            if (st[i][j] & (1 << 5)) sx = i, sy = j;
            if (st[i][j] & (1 << 6)) ex = i, ey = j;
        }
    for (int ca = 1; ca < T; ca++) {
        for (int i = 1; i <= 6; i++)
            for (int j = 1; j <= 6; j++) {
                scanf("%d", &tmp[i][j]);
                if (tmp[i][j] & (1 << 5)) sx1 = i, sy1 = j;
                if (tmp[i][j] & (1 << 6)) ex1 = i, ey1 = j;
            }
        solve();
        for (int i = 1; i <= 6; i++)
            for (int j = 1; j <= 6; j++) {
                st[i][j] = tmp[i][j];
                if (st[i][j] & (1 << 5)) sx = i, sy = j;
                if (st[i][j] & (1 << 6)) ex = i, ey = j;
            }
    }
    return 0;
}
