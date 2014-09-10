#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 100010;
const int INF = 1000000000;
int a[MAXN], n, ans, l[MAXN], r[MAXN];

void init() {
    ans = 0;
}

void input() {
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
}

void work() {
    a[0] = INF;
    for (int i = 1; i <= n; i++) {
        if (a[i] > a[i-1]) {
            l[i] = l[i-1] + 1;
        } else {
            l[i] = 1;
        }
    }
    a[n+1] = -1;
    for (int i = n; i >= 1; i--) {
        if (a[i] < a[i+1]) {
            r[i] = r[i+1] + 1;
        } else {
            r[i] = 1;
        }
    }
    l[0] = r[n+1] = 0;
    for (int i = 1; i <= n; i++) {
        //cout << l[i] << " " << r[i] << endl;
        if (a[i-1] + 1 < a[i+1]) {
            ans = max(ans, l[i-1] + 1 + r[i+1]);
        } else {
            ans = max(ans, max(l[i-1] + 1, 1 + r[i+1]));
        }
    }
}

void output() {
    cout << ans << endl;
}

int main() {
    while (cin >> n) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
