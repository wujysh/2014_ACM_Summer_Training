#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 100010;
bool visited[MAXN];
int n, p[25], b[MAXN];
long long sum;

struct A {
    int a;
    int pos;
    bool operator<(const A &x) const {
        return a > x.a;
    }
} a[MAXN];

void init() {
    memset(visited, false, sizeof(visited));
    sum = 0;
    p[0] = 1;
    for (int i = 1; i < 20; i++) {
        p[i] = p[i-1] * 2;
    }
}

void input() {
    for (int i = 0; i <= n; i++) {
        scanf("%d", &a[i].a);
        a[i].pos = i;
    }
}

void solve() {
    sort(a, a+n+1);

    int maxa = p[upper_bound(p, p+20, a[0].a) - p] - 1;
    //cout << maxa << endl;

    for (int i = 0; i <= n; i++) {
        while (maxa - a[i].a > n || visited[maxa - a[i].a]) {
            maxa >>= 1;
        }
        int bb = maxa - a[i].a;
        visited[bb] = true;
        b[a[i].pos] = bb;
        sum += (a[i].a | bb);
    }
}

void output() {
    printf("%I64d\n", sum);
    for (int i = 0; i <= n; i++) {
        if (i) printf(" ");
        printf("%d", b[i]);
    }
    printf("\n");
}

int main() {
    while (~scanf("%d", &n)) {
        init();
        input();
        solve();
        output();
    }
    return 0;
}
