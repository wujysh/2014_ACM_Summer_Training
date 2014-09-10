#include <iostream>
using namespace std;

long long k, p;

int main() {
    ios::sync_with_stdio(false);
    while (cin >> k >> p) {
        if ((k / (p-1)) & 1) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}

