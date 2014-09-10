#include <iostream>
using namespace std;

int k;

int main() {
    ios::sync_with_stdio(false);
    while (cin >> k) {
        bool flag = true;
        for (int i = 1; i < 65; i++) {
            if ((18 + k*i) % 65 == 0) {
                cout << i << endl;
                flag = false;
                break;
            }
        }
        if (flag) {
            cout << "no" << endl;
        }
    }
    return 0;
}
