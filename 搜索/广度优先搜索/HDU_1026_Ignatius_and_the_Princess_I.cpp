#include <iostream>
#include <cstring>
#include <string>
#include <queue>
using namespace std;

const int MAXN = 110;
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
string graph[MAXN];
int ans, n, m;
bool visited[MAXN][MAXN];

struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};
vector<Point> path;

struct State {
    int x, y, step;
    vector<Point> path;
    State(int _x, int _y, int _step, vector<Point> _path) : x(_x), y(_y), step(_step), path(_path) {}
    bool operator<(const State &b) const {
        return step > b.step;
    }
};
priority_queue<State> q;

void init() {
    memset(visited, false, sizeof(visited));
    while (!q.empty()) q.pop();
    ans = -1;
    path.clear();
}

void input() {
    cin.ignore();
    for (int i = 0; i < n; i++) {
        getline(cin, graph[i]);
    }
}

void work() {
    path.push_back(Point(0, 0));
    q.push(State(0, 0, 0, path));
    visited[0][0] = true;

    while (!q.empty()) {
        State cur = q.top();
        q.pop();

        if (cur.x == n-1 && cur.y == m-1) {
            ans = cur.step;
            path = cur.path;
            return;
        }

        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i], ny = cur.y + dy[i];
            vector<Point> npath = cur.path;
            npath.push_back(Point(nx, ny));
            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                if (!visited[nx][ny]) {
                    visited[nx][ny] = true;
                    if (graph[nx][ny] == '.') {
                        q.push(State(nx, ny, cur.step + 1, npath));
                    } else if (isdigit(graph[nx][ny])) {
                        q.push(State(nx, ny, cur.step + 1 + graph[nx][ny] - '0', npath));
                    }
                }
            }
        }
    }
}

void output() {
    if (ans == -1) {
        cout << "God please help our poor hero." << endl;
    } else {
        cout << "It takes " << ans << " seconds to reach the target position, let me show you the way." << endl;
        int cnt = 1;
        for (int i = 1; i < path.size(); i++) {
            cout << cnt++ << "s:" << '(' << path[i-1].x << ',' << path[i-1].y << ')' << "->" << '(' << path[i].x << ',' << path[i].y << ')' << endl;
            if (isdigit(graph[path[i].x][path[i].y])) {
                for (int j = 0; j < graph[path[i].x][path[i].y] - '0'; j++) {
                    cout << cnt++ << "s:FIGHT AT " << '(' << path[i].x << ',' << path[i].y << ')' << endl;
                }
            }
        }
    }
    cout << "FINISH" << endl;
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
