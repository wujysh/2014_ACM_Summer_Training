#include <iostream>
using namespace std;

long long x, y;

long long gcd(long long x, long long y) {
    return y == 0 ? x : gcd(y, x % y);
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> x >> y) {
        long long Max = max(x, y), Min = min(x, y);/*
        if (Max % Min == 0) {
            cout << Max << endl;
        } else {
            cout << Max + Max % Min * Min - Max % Min << endl;
        }*/
        cout << Min+Max - gcd(Min, Max) << endl;
    }
    return 0;
}
