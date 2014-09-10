#include <iostream>
using namespace std;

long long n;

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n) {
        cout << (1 + n) * n / 2 << endl;
        cout << endl;
    }
    return 0;
}
