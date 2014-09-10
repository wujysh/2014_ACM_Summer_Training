#include <iostream>
#include <cmath>
using namespace std;

int nCase, n;

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        cin >> n;
        cout << (((int)sqrt(n/1.0) + (int)sqrt(n/2.0)) % 2) << endl;
    }
    return 0;
}
