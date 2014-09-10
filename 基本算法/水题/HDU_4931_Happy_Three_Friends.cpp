#include <iostream>
#include <algorithm>
using namespace std;

int nCase, a[10];

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        for (int i = 0; i < 6; i++) {
            cin >> a[i];
        }
        sort(a, a+6);
        int aa = a[5] + a[4];
        int bb = a[3] + a[2] + a[1];
        if (aa > bb) {
            cout << "Grandpa Shawn is the Winner!" << endl;
        } else {
            cout << "What a sad story!" << endl;
        }
    }
    return 0;
}
