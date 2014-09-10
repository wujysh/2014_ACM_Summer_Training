#include <iostream>
using namespace std;

const int MAXN = 25;
const int outer[][2] = {{1,4},{2,7},{3,4},{8,7},{17,18},{22,21},{23,18},{24,21}};
const int inner[] = {4,5,6,7,9,10,11,12,13,14,15,16,18,19,20,21};
int a[MAXN], b[MAXN], nCase;

void input() {
    for (int i = 1; i <= 24; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= 24; i++) {
        cin >> b[i];
    }
}

bool judge1() {
    for (int i = 0; i < 8; i++) {
        if (a[outer[i][0]] == 0) {
            swap(a[outer[i][0]], a[outer[i][1]]);
        }
        if (b[outer[i][0]] == 0) {
            swap(b[outer[i][0]], b[outer[i][1]]);
        }
        if (a[outer[i][0]] != b[outer[i][0]]) {
            return false;
        }
    }
    return true;
}

bool judge2() {
    int cnt1 = 0, cnt2 = 0, row1, row2;
    for (int i = 0; i < 16; i++) {
        if (a[inner[i]] == 0) {
            row1 = i / 4;
            continue;
        }
        for (int j = 0; j < i; j++) {
            if (a[inner[j]] > a[inner[i]]) {
                cnt1++;
            }
        }
    }
    for (int i = 0; i < 16; i++) {
        if (b[inner[i]] == 0) {
            row2 = i / 4;
            continue;
        }
        for (int j = 0; j < i; j++) {
            if (b[inner[j]] > b[inner[i]]) {
                cnt2++;
            }
        }
    }
    if ((cnt1 + row1) % 2 == (cnt2 + row2) % 2) {
        return true;
    } else {
        return false;
    }
}

void solve() {
    if (judge1()) {
        if (judge2()) {
            cout << "N" << endl;
        } else {
            cout << "Y" << endl;
        }
    } else {
        cout << "Y" << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        input();
        solve();
    }
    return 0;
}
