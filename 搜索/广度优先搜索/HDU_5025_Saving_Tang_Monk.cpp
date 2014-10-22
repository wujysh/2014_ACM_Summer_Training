#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN = 110;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
char graph[MAXN][MAXN];
int num[MAXN][MAXN], cnt;
bool visited[MAXN][MAXN][10][1 << 6];
int N, M;

struct State {
    int x, y, step, key, snake;
    State() {}
    State(int _x, int _y, int _step, int _key, int _snake) : x(_x), y(_y), step(_step), key(_key), snake(_snake) {}
    bool operator<(const State &b) const {
        return step > b.step;
    }
} K, T;

bool judge(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= N) return false;
    if (graph[x][y] == '#') return false;
    return true;
}

void solve() {
    cnt = 1;
    memset(num, 0, sizeof(num));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (graph[i][j] == 'K') {
                //cout << "!!!" << endl;
                K.x = i;  K.y = j;
            }
            if (graph[i][j] == 'T') {
                T.x = i;  T.y = j;
            }
            if (graph[i][j] == 'S') {
                num[i][j] = cnt++;
            }
        }
    }
    //cout << K.x << " " << K.y << endl;
    //cout << T.x << " " << T.y << endl;

    memset(visited, 0, sizeof(visited));
    priority_queue<State> q;
    q.push(State(K.x, K.y, 0, 0, 0));
    visited[K.x][K.y][0][0] = true;

    while (!q.empty()) {
        State cur = q.top();
        q.pop();

        //cout << cur.x << " " << cur.y << " " << cur.key << " " << cur.step << endl;
        if (cur.x == T.x && cur.y == T.y && cur.key == M) {
            printf("%d\n", cur.step);
            return;
        }

        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i], ny = cur.y + dy[i], nk = cur.key, ns = cur.snake, nt = cur.step;
            if (judge(nx, ny)) {
                if (graph[nx][ny] >= '1' && graph[nx][ny] <= '9') {
                    if (graph[nx][ny] - '0' == cur.key + 1) {
                        nk = cur.key + 1;
                        //cout << nk << endl;
                    }
                }
                bool flag = false;
                if (graph[nx][ny] == 'S') {
                    if (!(ns & (1 << num[nx][ny]))) {
                        ns |= (1 << num[nx][ny]);
                        flag = true;
                    }
                }
                if (!visited[nx][ny][nk][ns]) {
                    visited[nx][ny][nk][ns] = true;
                    if (flag) {
                        q.push(State(nx, ny, cur.step+2, nk, ns));
                    } else {
                        q.push(State(nx, ny, cur.step+1, nk, ns));
                    }
                }
            }

        }

    }
    printf("impossible\n");
}

void input() {
    for (int i = 0; i < N; i++) {
        scanf("%s", graph[i]);
        //cout << graph[i] << endl;
    }
}

int main() {
    while (~scanf("%d%d", &N, &M) && (N || M)) {
        input();
        solve();
    }
    return 0;
}
