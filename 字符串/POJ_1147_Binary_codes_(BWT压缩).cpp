#include <iostream>
using namespace std;

const int MAXN = 3010;
int a[MAXN], b[MAXN], cnt, n;

void init() {
    cnt = 0;
}

void input() {
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
}

void solve() {
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            b[cnt++] = i;
        }
    }
    for (int i = 0; i < n; i++) {
        if (a[i] == 1) {
            b[cnt++] = i;
        }
    }

    int t = 0;
    for (int i = 0; i < n; i++) {
        cout << a[b[t]] << " ";
        t = b[t];
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n) {
        init();
        input();
        solve();
    }
	return 0;
}
