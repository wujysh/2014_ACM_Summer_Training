#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

const int MAXN = 100010;
int n;

struct Building {
    int w, s;
    Building() {}
    Building(int _w, int _s) : w(_w), s(_s) {}
    bool operator<(const Building &b) const {
        return w + s < b.w + b.s;
    }
} building[MAXN];

void input() {
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &building[i].w, &building[i].s);
    }
}

void solve() {
    sort(building, building+n);
    long long sum = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, sum - building[i].s);
        sum += building[i].w;
    }
    printf("%I64d\n", ans);
}

int main() {
    while (~scanf("%d", &n)) {
        input();
        solve();
    }
    return 0;
}
