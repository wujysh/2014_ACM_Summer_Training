#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <queue>
using namespace std;

const int dx[5] = {0, 0, -1, 1, 0}, dy[5] = {0, -1, 0, 0, 1};
const int INF = 0x3f3f3f3f;
const int MAXN = 210;
char graph[MAXN][MAXN];
int N, M, start_x, start_y, nKey, ans, allGet;
bool visited[MAXN][MAXN][5][1<<7];

struct State {
    int step, x, y, ori, get;  // 0-Initial, 1-L, 2-U, 3-D, 4-R
    State(int _step, int _x, int _y, int _ori, int _get) :
        step(_step), x(_x), y(_y), ori(_ori), get(_get) {}
    bool operator<(const State &b) const {
        return step > b.step;
    }
};
priority_queue<State> q;

void init() {
    ans = INF;
    allGet = nKey = 0;
    while (!q.empty()) q.pop();
    memset(visited, false, sizeof(visited));
}

void input() {
    for (int i = 0; i < N; i++) {
        scanf("%s", &graph[i]);
        for (int j = 0; j < M; j++) {
            if (graph[i][j] == 'S') {
                start_x = i;  start_y = j;
            } else if (graph[i][j] == 'K') {
                graph[i][j] = '0' + nKey;
                nKey++;
                allGet = (allGet << 1) + 1;
                //cout << nKey << " " << graph[i][j] << endl;
            }
        }
    }
    //cout << "allGet: " << allGet << endl;
}

void work() {
    q.push(State(0, start_x, start_y, 0, 0));
    for (int i = 1; i <= 4; i++) {
        visited[start_x][start_y][i][0] = true;
    }

    while (!q.empty()) {
        State cur = q.top();
        q.pop();

        if (visited[cur.x][cur.y][cur.ori][cur.get]) continue;
        visited[cur.x][cur.y][cur.ori][cur.get] = true;

        //cout << cur.step << " " << cur.x << " " << cur.y << " " << cur.ori << " " << cur.get << endl;

        if (graph[cur.x][cur.y] == 'E' && cur.get == allGet) {
            ans = cur.step;
            return;
        }

        if (graph[cur.x][cur.y] == 'L') {
            cur.ori = 1;
        } else if (graph[cur.x][cur.y] == 'U') {
            cur.ori = 2;
        } else if (graph[cur.x][cur.y] == 'D') {
            cur.ori = 3;
        } else if (graph[cur.x][cur.y] == 'R') {
            cur.ori = 4;
        } else if (graph[cur.x][cur.y] >= '0' && graph[cur.x][cur.y] <= '6') {
            cur.get |= 1 << (graph[cur.x][cur.y] - '0');
        }

        int nx = cur.x + dx[cur.ori], ny = cur.y + dy[cur.ori];
        if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
            if (graph[nx][ny] != '#' && cur.ori != 0) {  // go ahead
                q.push(State(cur.step, nx, ny, cur.ori, cur.get));
                //visited[cur.x][cur.y][cur.ori][cur.get] = false;
            } else {
                for (int i = 1; i <= 4; i++) {
                    int nnx = cur.x + dx[i], nny = cur.y + dy[i];
                    if (nnx >= 0 && nnx < N && nny >= 0 && nny < M) {
                        if (graph[nnx][nny] != '#') {
                            q.push(State(cur.step+1, nnx, nny, i, cur.get));
                        }
                    }
                }
            }
        }
    }
}

void output() {
    if (ans == INF) {
        printf("-1\n");
    } else {
        printf("%d\n", ans);
    }
}

int main() {
    while (scanf("%d%d", &N, &M) == 2) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
