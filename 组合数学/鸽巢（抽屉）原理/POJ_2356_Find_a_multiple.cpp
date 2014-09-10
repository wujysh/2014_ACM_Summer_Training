#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 10010;
int a[MAXN], sum[MAXN], pos[MAXN], n, p, q;

void init() {
    sum[0] = 0;
    p = q = 0;
    memset(pos, 0, sizeof(pos));
}

void input() {
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i-1] + a[i];
        //cout << sum[i] << " ";
    }
}

void work() {
    for (int i = n; i >= 1; i--) {
        if (sum[i] % n == 0) {
            p = 1;  q = i;
            //cout << endl << p << "-" << q << endl;
            return;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (pos[sum[i] % n] != 0) {
            if (i - pos[sum[i] % n] > q - p) {
                p = pos[sum[i] % n] + 1;
                q = i;
            }
        } else {
            pos[sum[i] % n] = i;
        }
    }
}

void output() {
    cout << q - p + 1<< endl;
    for (int i = p; i <= q; i++) {
        cout << a[i] << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
