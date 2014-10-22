#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 55;
int n, a[MAXN], nCase;
double sum;

void input() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
}

bool cmp(int a, int b) {
    return a > b;
}

void solve() {
    sort(a, a+n, cmp);
    sum = 0;
    for (int i = 0; i < n; i++) {
        sum += pow(0.95, i) * a[i];
    }
    cout << fixed << setprecision(10) << sum << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        input();
        solve();
    }
    return 0;
}
