#include <iostream>
#include <cmath>
using namespace std;

const int MAXN = 100010;
int nCase, distSum[MAXN], distToO[MAXN], weightSum[MAXN], C, N;
int dp[MAXN], q[MAXN], head, tail;

struct Package {
    int x, y, w;
} packages[MAXN];

void init() {
    head = tail = 0;
    q[tail++] = 0;
    distSum[0] = weightSum[0] = packages[0].x = packages[0].y = 0;
}

void input() {
    cin >> C;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> packages[i].x >> packages[i].y >> packages[i].w;
        distToO[i] = abs(packages[i].x + packages[i].y);
        distSum[i] = distSum[i-1] + abs(packages[i].x - packages[i-1].x) + abs(packages[i].y - packages[i-1].y);
        weightSum[i] = weightSum[i-1] + packages[i].w;
    }
}

int func(int j) {
    return dp[j] - distSum[j+1] + distToO[j+1];
}

void work() {
    for (int i = 1; i <= N; i++) {
        while (head+1 < tail && weightSum[i] - weightSum[q[head]] > C) {
            head++;
        }

        dp[i] = func(q[head]) + distSum[i] + distToO[i];

        while (head+1 < tail && func(i) <= func(q[tail-1])) {
            tail--;
        }
        q[tail++] = i;
    }
}

void output() {
    cout << dp[N] << endl;
    if (nCase) cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
