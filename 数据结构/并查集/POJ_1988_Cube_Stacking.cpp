#include <iostream>
#include <vector>
#include <map>
using namespace std;

const int MAXN = 30010;
int p;
int father[MAXN], sum[MAXN], num[MAXN];

void init() {
    for (int i = 1; i <= 30000; i++) {
        father[i] = i;
        sum[i] = 0;
        num[i] = 1;
    }
}

int find_set(int x) {
    int tmp = father[x];
    if (father[x] != x) {
        father[x] = find_set(father[x]);
        sum[x] += sum[tmp];
    }
    return father[x];
}

void union_set(int x, int y) {
    x = find_set(x);
    y = find_set(y);
    if (x == y) return;
    father[x] = y;
    sum[x] += num[y];
    num[y] += num[x];
}

void solve() {
    for (int k = 0; k < p; k++) {
        char op;
        cin >> op;
        if (op == 'M') {
            int x, y, posx;
            cin >> x >> y;
            union_set(x, y);
        } else if (op == 'C') {
            int x, cnt = 0;
            cin >> x;
            find_set(x);
            cout << sum[x] << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> p) {
        init();
        solve();
    }
    return 0;
}
