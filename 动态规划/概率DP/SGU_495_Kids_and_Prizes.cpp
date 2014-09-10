#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int N, M;
double ans;

int main() {
    while (cin >> N >> M) {
        ans = (double)N * (1.0 - pow((1.0 - 1.0 / N), M));
        cout << fixed << setprecision(9) << ans << endl;
    }
    return 0;
}

