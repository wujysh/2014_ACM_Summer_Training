#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

const int INF = 0x3f3f3f3f;
int n, nCase, ans;

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        cin >> n;
        ans = INF;
        for (int i = 1; i <= sqrt(n); i++) {
            if (n % i == 0) {
                int a = i;
                int b = n / a;
                if (a != b && a % 2 == b % 2) {
                    int x = abs(b - a) / 2;
                    ans = min(ans, x);
                }
            }
        }
        if (ans == INF) {
            cout << -1 << endl;
        } else {
            cout << ans << endl;
        }
    }
    return 0;
}
