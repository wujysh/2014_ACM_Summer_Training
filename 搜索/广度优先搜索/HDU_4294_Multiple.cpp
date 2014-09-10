#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN = 10010;
int visited[MAXN], digit[MAXN], pre[MAXN], n, k;
bool flag;
string ans;

bool bfs(int m, int num[]) {
    queue<int> q;
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < m; i++) {
        int x = num[i];
        int next = x % n;
        if (x != 0 && !visited[next]) {
            pre[next] = -1;
            visited[next] = 1;
            digit[next] = x;
            q.push(next);
        }
    }

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        if (cur == 0) return true;
        if (!ans.empty() && visited[cur] > ans.size()) return false;

        for (int i = 0; i < m; i++) {
            int x = num[i];
            int next = (cur * k + x) % n;
            if (!visited[next]) {
                pre[next] = cur;
                visited[next] = visited[cur] + 1;
                digit[next] = num[i];
                q.push(next);
            }
        }
    }

    return false;
}

inline string genAns() {
    int x = 0;
    string ans;
    ans.resize(visited[x]);
    while (x != -1) {
        ans[visited[x]-1] = digit[x] + '0';
        x = pre[x];
    }
    return ans;
}

inline bool cmpAns(string str) {
    if (ans.empty()) return true;
    if (str.size() > ans.size()) return false;
    if (str.size() < ans.size()) return true;
    if (str < ans) return true;
    return false;
}

void init() {
    flag = false;
    ans = "";
}

void solve() {
    int num[2];
    for (int i = 1; i < k; i++) {
        num[0] = i;
        if (bfs(1, num)) {
            string str = genAns();
            flag = true;
            if (cmpAns(str)) {
                ans = str;
            }
        }
    }
    if (!flag) {
        for (int i = 1; i < k; i++) {
            for (int j = 0; j < i; j++) {
                num[0] = j;  num[1] = i;
                if (bfs(2, num)) {
                    string str = genAns();
                    if (cmpAns(str)) {
                        ans = str;
                    }
                }
            }
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> k) {
        init();
        solve();
    }
    return 0;
}
