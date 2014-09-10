#include <iostream>
using namespace std;

const int mod = 2011;
int N, M1, M2;

int pow_mod(int a, int i) {
    if (i == 0) return 1 % mod;
    int temp = pow_mod(a, i >> 1);
    temp = temp * temp % mod;
    if (i & 1) temp = temp * a % mod;
    return temp;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> N && N) {
        M1 = ((pow_mod(6, N) + 24) % mod + mod) % mod * 1944 % mod;
        M2 = ((pow_mod(6, N) - 1) % mod + mod) % mod * 1609 % mod;
        cout << M1 << " " << M2 << endl;
    }
    return 0;
}
