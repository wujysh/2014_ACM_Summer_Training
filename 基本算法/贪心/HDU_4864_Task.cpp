#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 110;
struct Node {
    int x, y;
    bool operator<(const Node &b) const {
        if (x == b.x) {
            return y > b.y;
        } else {
            return x > b.x;
        }
    }
};
vector<Node> machine, task;
long long ans1, ans2;
int n, m, cnt[MAXN];

void init() {
    machine.clear();
    task.clear();
    memset(cnt, 0, sizeof(cnt));
    ans1 = ans2 = 0;
}

void input() {
    machine.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> machine[i].x >> machine[i].y;
    }
    task.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> task[i].x >> task[i].y;
    }
}

void work() {
    sort(task.begin(), task.end());
    sort(machine.begin(), machine.end());
    int index = -1;
    for (int i = 0; i < m; i++) {
        for (int j = index+1; j < n; j++) {
            if (machine[j].x >= task[i].x) {
                cnt[machine[j].y]++;
                index = j;
            } else {
                index = j - 1;
                break;
            }
        }
        for (int j = task[i].y; j <= 100; j++) {
            if (cnt[j]) {
                ans1++;
                ans2 += 500*task[i].x + 2*task[i].y;
                cnt[j]--;
                break;
            }
        }
    }
}

void output() {
    cout << ans1 << " " << ans2 << endl;
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
