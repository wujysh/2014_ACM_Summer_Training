//#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 10010;
const int MAXM = 100010;
int ans[MAXM], father[MAXN], rank[MAXN], cnt, N, M;

struct Line {
    int x, y;
} line[MAXM];

void init() {
    for (int i = 0; i < N; i++) {
        father[i] = i;
    }
    cnt = N;
}

int find(int v) {
    return father[v] = father[v] == v ? v : find(father[v]);
}

void merge(int x, int y) {
    int a = find(x), b = find(y);
    if (rank[a] < rank[b]) {
        father[a] = b;
    } else {
        father[b] = a;
        if (rank[b] == rank[a]) {
            rank[a]++;
        }
    }
    cnt--;
}

void input() {
    for (int i = 0; i < M; i++) {
        //cin >> line[i].x >> line[i].y;
        scanf("%d%d", &line[i].x, &line[i].y);
    }
}

void work() {
    for (int i = M-1; i >= 0; i--) {
        ans[i] = cnt;
        if (find(line[i].x) != find(line[i].y)) {
            merge(line[i].x, line[i].y);
        }
    }
}

void output() {
    for (int i = 0; i < M; i++) {
        //cout << ans[i] << endl;
        printf("%d\n", ans[i]);
    }
}

int main() {
    //ios::sync_with_stdio(false);
    //while (cin >> N >> M) {
    while (scanf("%d%d", &N, &M) == 2) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
