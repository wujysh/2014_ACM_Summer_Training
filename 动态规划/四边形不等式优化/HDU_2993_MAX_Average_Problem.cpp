// AC by Visual C++, but TLE by GNU C++
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100010;
int a[MAXN], sum[MAXN], q[MAXN], head, tail, n, k;
double ans;

bool useless(long long Xa, long long Xb, long long Xc) {
    return (sum[Xc] - sum[Xb]) * (Xb - Xa) <= (sum[Xb] - sum[Xa]) * (Xc - Xb);
}

void init() {
    head = 0;  tail= -1;
    ans = 0;
    sum[0] = 0;
}

void input() {
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum[i] = sum[i-1] + a[i];
    }
}

void work() {
    for (int i = k; i <= n; i++) {
        while (head < tail && useless(q[tail-1], q[tail], i - k)) {
            tail--;
        }

        q[++tail] = i - k;

        while (head < tail && useless(q[head+1], q[head], i)) {
            head++;
        }

        ans = max(ans, (sum[i] - sum[q[head]]) * 1.0 / (i - q[head]));
    }
}

void output() {
    printf("%.2lf\n", ans);
}

int main() {
    while (scanf("%d%d", &n, &k) == 2) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
