#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
using namespace std;

const int MAXN = 4;
const int dxy[] = {-3, 3, -1, 1};
const char dir[] = "udlr";
const int fac[] = {40320, 5040, 720, 120, 24, 6, 2, 1, 1}; //康拖展开
struct State {
    int xy;
    string puzzle, path;
    State() {}
    State(int xy0, string p0, string path0) {
        xy = xy0;
        puzzle = p0;
        path = path0;
    }
} initialState, resultState, q[100000];
bool visited[400000];
string initialPuzzle, resultPuzzle = "123456789", line;
int initialXY, head, tail;

void init() {
    initialPuzzle = "";
    memset(visited, false, sizeof(visited));
}

inline int kangtuo(string &puzzle) {  // 求康拓展开的值
    int sum = 0;
    for (int i = 0; i < 9; i++) {
        int cnt = 0;
        for (int j = i+1; j < 9; j++) {
            if (puzzle[i] > puzzle[j]) {
                cnt++;
            }
        }
        sum += cnt * fac[i];
    }
    return sum + 1;
}

void input() {
    stringstream ss(line);
    for (int i = 0; i < 9; i++) {
        char ch;
        ss >> ch;
        if (ch == 'x') {
            initialXY = i;
            initialPuzzle += '9';
        } else {
            initialPuzzle += ch;
        }
    }
}

void work() {
    //queue<State> q;
    //q.push(State(initialXY, initialPuzzle, 0, ""));
    visited[kangtuo(initialPuzzle)] = true;
    head = tail = 0;
    //State q[MAXN];
    q[tail++] = State(initialXY, initialPuzzle, "");
    //while (!q.empty()) {
    while (head < tail) {
        //State cur = q.front();
        State cur = q[head];
        //q.pop();
        head++;

        if (cur.puzzle == resultPuzzle) {
            resultState = cur;
            return;
        }

        for (int i = 0; i < 4; i++) {
            int nxy = cur.xy + dxy[i];
            if (nxy < 0 || nxy > 8) continue;
            if (i == 2 && (cur.xy == 3 || cur.xy == 6)) continue;
            if (i == 3 && (cur.xy == 2 || cur.xy == 5)) continue;

            string nextPuzzle = cur.puzzle;
            swap(nextPuzzle[cur.xy], nextPuzzle[nxy]);
            int token = kangtuo(nextPuzzle);
            if (!visited[token]) {
                q[tail++] = State(nxy, nextPuzzle, cur.path+dir[i]);
                //q.push(State(nxy, nextPuzzle, cur.distance+1, cur.path+dir[i]));
                visited[token] = true;
                if (token == 0) return;
            }
        }
    }
}

void output() {
    if (visited[kangtuo(resultPuzzle)]) {
        cout << resultState.path << endl;
    } else {
        cout << "unsolvable" << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    while (getline(cin, line)) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
