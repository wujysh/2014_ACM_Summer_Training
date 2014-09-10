#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN = 10010;
int inDegree[MAXN], ans, cnt, n, m;
vector<int> child[MAXN];

struct State {
    int reward, node;
    State(int _reward, int _node) : reward(_reward), node(_node) {}
};
queue<State> q;

void init() {
    memset(inDegree, 0, sizeof(inDegree));
    for (int i = 0; i <= n; i++) {
        child[i].clear();
    }
    ans = cnt = 0;
    while (!q.empty()) q.pop();
}

void input() {
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        inDegree[a]++;
        child[b].push_back(a);
    }
}

void work() {
    for (int i = 1; i <= n; i++) {
        if (inDegree[i] == 0) {
            q.push(State(888, i));
            cnt++;
        }
    }
    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        ans += cur.reward;

        for (int i = 0; i < child[cur.node].size(); i++) {
            inDegree[child[cur.node][i]]--;
            if (inDegree[child[cur.node][i]] == 0) {
                q.push(State(cur.reward+1, child[cur.node][i]));
                cnt++;
            }
        }
    }
}

void output() {
    if (cnt == n) {
        cout << ans << endl;
    } else {
        cout << -1 << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> m) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
