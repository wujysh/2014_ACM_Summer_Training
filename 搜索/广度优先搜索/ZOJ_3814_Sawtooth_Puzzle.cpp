#include <iostream>
#include <cstring>
#include <string>
#include <queue>
using namespace std;

const int MAXN = 10;
const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {-1, 0, 1, 0};
string initial_image[MAXN], target_image[MAXN];
int nCase;//, pre[1 << 18];
vector<int> targets;
bool edge[MAXN][4], visited[1 << 18], vis[MAXN];

struct State {
    int image;
    int step;
    State() {}
    State(int _image, int _step) : image(_image), step(_step) {}
};

void debug_print_state(int state) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) cout << endl;
        cout << state % 4 << " ";
        state >>= 2;
    }
    cout << endl;
}

inline string rotate_right(string src) {
    string ret = src;
    int cnt = 0;
    for (int j = 7; j >= 0; j--) {
        for (int i = 0; i < 8; i++) {
            ret[i * 8 + j] = src[cnt++];
        }
    }
    return ret;
}

void input() {
    for (int i = 0; i < 3; i++) {
        string x, y, z;
        for (int j = 0; j < 8; j++) {
            string a, b, c;
            cin >> a >> b >> c;
            x += a;
            y += b;
            z += c;
        }
        initial_image[i * 3] = x;
        initial_image[i * 3 + 1] = y;
        initial_image[i * 3 + 2] = z;
    }
    for (int i = 0; i < 3; i++) {
        string x, y, z;
        for (int j = 0; j < 8; j++) {
            string a, b, c;
            cin >> a >> b >> c;
            x += a;
            y += b;
            z += c;
        }
        target_image[i * 3] = x;
        target_image[i * 3 + 1] = y;
        target_image[i * 3 + 2] = z;
    }
    for (int i = 0; i < 9; i++) {
        cin >> edge[i][0] >> edge[i][1] >> edge[i][2] >> edge[i][3];  // left, top, right, bottom
    }
}

inline int change(int src, int i, int x) {
    int ret = src;
    ret &= ((1 << 18) - 1 - (3 << (2 * i)));
    if (x == 1) {
        ret |= 1 << (2 * i);
    } else if (x == 2) {
        ret |= 1 << (2 * i + 1);
    } else if (x == 3) {
        ret |= 3 << (2 * i);
    }
    return ret;
}

inline int get(int src, int i) {
    int ret = 0;
    if (src & (1 << (2 * i))) {
        ret |= 1;
    }
    if (src & (1 << (2 * i + 1))) {
        ret |= 2;
    }
    return ret;
}

void generate_targets(int state, int step) {
    if (step == 9) {
        targets.push_back(state);
        return;
    }
    string r_image = initial_image[step];
    for (int i = 0; i < 4; i++) {
        if (r_image == target_image[step]) {
            generate_targets(change(state, step, i), step + 1);
        }
        r_image = rotate_right(r_image);
    }
}

void init() {
    targets.clear();
    generate_targets(0, 0);
}

int change_meshed(int src, int i, int direct) {
    int ret = src;

    vis[i] = true;

    int x = i / 3, y = i % 3;
    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx < 0 || nx > 2 || ny < 0 || ny > 2) continue;
        int ni = nx * 3 + ny;
        if (edge[i][(d - get(ret, i) + 4) % 4] && edge[ni][(d + 2 - get(ret, ni) + 4) % 4]) {
            if (!vis[ni]) {
                ret = change_meshed(ret, ni, -direct);
            }
        }
    }
    ret = change(ret, i, (get(ret, i) + direct + 4) % 4);

    return ret;
}

void solve() {
    queue<State> q;
    q.push(State(0, 0));
    memset(visited, false, sizeof(visited));
    visited[0] = true;
    //memset(pre, -1, sizeof(pre));

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        for (int i = 0; i < targets.size(); i++) {
            if (cur.image == targets[i]) {
                //debug_print_state(cur.image);
                /*int x = cur.image;
                while (x != -1) {
                    cout << x << ": " << endl;
                    debug_print_state(x);
                    x = pre[x];
                }*/
                cout << cur.step << endl;
                return;
            }
        }

        for (int i = 0; i < 9; i++) {
            memset(vis, false, sizeof(vis));
            int nimage = change_meshed(cur.image, i, 1);
            if (!visited[nimage]) {
                visited[nimage] = true;
                q.push(State(nimage, cur.step + 1));
                //pre[nimage] = cur.image;
            }
        }
    }

    cout << -1 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        input();
        init();
        solve();
    }
    return 0;
}
