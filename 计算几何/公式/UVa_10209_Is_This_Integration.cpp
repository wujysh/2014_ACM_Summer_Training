#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const double PI = acos(-1.0);
double a, A, B, C;

int main() {
    ios::sync_with_stdio(false);
    while (cin >> a) {
        A = (1.0 - sqrt(3) + PI / 3.0) * a*a;
        B = (-4.0 + 2.0*sqrt(3) + PI / 3.0) * a*a;
        C = (4.0 - sqrt(3) - 2.0 / 3.0 * PI) * a*a;
        cout << fixed << setprecision(3) << A << " " << B << " " << C << endl;
    }
    return 0;
}
