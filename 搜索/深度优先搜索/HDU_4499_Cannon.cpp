#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 10;
int N, M, Q, ans, graph[MAXN][MAXN], dp[MAXN][MAXN];

void dfs(int x, int y, int cnt) {

    if (x >= N) {
        ans = max(ans, cnt);/*
        if (cnt >= 7) {
        for (int i = 0; i<N; i++) {
            for (int j = 0; j < M; j++) {
                cout << graph[i][j];
            }
            cout << endl;
        }
        cout << endl;
        }*/
        return;
    }
    if (y >= M) {
        dfs(x+1, 0, cnt);
        return;
    }
    if (graph[x][y] == 1) {
        dfs(x, y+1, cnt);
        return;
    }

    dfs(x, y+1, cnt);

    bool flag = false;
    for (int j = y-1; j >= 0; j--) {
        if (graph[x][j] && !flag) {
            flag = true;
            continue;
        }
        if (graph[x][j] == 1 && flag) {
            break;
        }
        if (graph[x][j] == 2 && flag) {
            return;
        }
    }

    flag = false;
    for (int i = x-1; i >= 0; i--) {
        if (graph[i][y] && !flag) {
            flag = true;
            continue;
        }
        if (graph[i][y] == 1 && flag) {
            break;
        }
        if (graph[i][y] == 2 && flag) {
            return;
        }
    }

    graph[x][y] = 2;
    //cout << x << " " << y << " " << cnt << endl;
    dfs(x, y+1, cnt+1);

    graph[x][y] = 0;
}

void init() {
    memset(graph, 0, sizeof(graph));
    ans = 0;
}

void input() {
    for (int i = 0; i < Q; i++) {
        int x, y;
        cin >> x >> y;
        graph[x][y] = 1;
    }
}

void work() {
    dfs(0, 0, 0);
}

void output() {
    cout << ans << endl;
}

int main() {
    while (cin >> N >> M >> Q) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
