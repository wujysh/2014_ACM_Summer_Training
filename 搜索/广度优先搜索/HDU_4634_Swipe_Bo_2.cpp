#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <queue>
using namespace std;

const int dx[5] = {0, 0, -1, 1, 0}, dy[5] = {0, -1, 0, 0, 1};
const int MAXN = 210;
char graph[MAXN][MAXN];
string dir = " LUDR";
int N, M, start_x, start_y, nKey, ans, allGet;
bool visited[MAXN][MAXN][5][1<<7];

struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};
//map<Point, Point> pre;

struct State {
    int step, x, y, ori, get;  // 0-Initial, 1-L, 2-U, 3-D, 4-R
    string path;
    State(int _step, int _x, int _y, int _ori, int _get, string _path) :
        step(_step), x(_x), y(_y), ori(_ori), get(_get), path(_path) {}
    //    State(int _step, int _x, int _y, int _ori, int _get) :
    //    step(_step), x(_x), y(_y), ori(_ori), get(_get) {}
};
queue<State> q;

void init() {
    //pre.clear();
    ans = -1;
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
                //allGet = (allGet << 1) + 1;
                //cout << nKey << " " << graph[i][j] << endl;
            }
        }
    }
    allGet = (1 << nKey) - 1;
    //cout << "allGet: " << allGet << endl;
}

void work() {
    q.push(State(0, start_x, start_y, 0, 0, ""));

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        //cout << cur.x << " " << cur.y << " " << cur.ori << " " << cur.get << " " << cur.step << endl;

        for (int i = 1; i <= 4; i++) {
            int nx = cur.x + dx[i], ny = cur.y + dy[i], nori = i, nget = cur.get;
            bool isWall = false;
            while (true) {
                if (nx < 0 || nx >= N || ny < 0 || ny >= M) break;

                if (visited[nx][ny][nori][nget]) break;
                visited[nx][ny][nori][nget] = true;

                if (graph[nx][ny] == '#') {
                    isWall = true;
                    break;
                }

                if (graph[nx][ny] == 'L') {
                    nori = 1;
                } else if (graph[nx][ny] == 'U') {
                    nori = 2;
                } else if (graph[nx][ny] == 'D') {
                    nori = 3;
                } else if (graph[nx][ny] == 'R') {
                    nori = 4;
                }


                if (graph[nx][ny] >= '0' && graph[nx][ny] <= '6') {
                    nget |= 1 << (graph[nx][ny] - '0');
                }

                if (graph[nx][ny] == 'E' && nget == allGet) {
                    ans = cur.step + 1;
                    cout << cur.path+dir[i] << endl;
                    return;
                }

                nx += dx[nori];  ny += dy[nori];
            }

            if (isWall) {
                //if (visited[nx-dx[nori]][ny-dy[nori]][nori][nget]) continue;
                //visited[nx-dx[nori]][ny-dy[nori]][nori][nget] = true;
                q.push(State(cur.step+1, nx-dx[nori], ny-dy[nori], nori, nget, cur.path+dir[i]+" "));
                //q.push(State(cur.step+1, nx-dx[nori], ny-dy[nori], nori, nget));
                //pre[Point(nx-dx[nori], ny-dy[nori])] = Point(cur.x, cur.y);
            }
        }
    }
}

void output() {
    printf("%d\n", ans);
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
