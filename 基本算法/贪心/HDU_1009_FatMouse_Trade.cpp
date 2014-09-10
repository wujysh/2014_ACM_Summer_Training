#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

const int MAXN = 1010;
int M, N;
double ans;
struct Room {
    int J, F;
    double JperF;
    bool operator<(const Room &b) const {
        return JperF > b.JperF;
    }
} room[MAXN];

void init() {
    ans = 0;
}

void input() {
    for (int i = 0; i < N; i++) {
        cin >> room[i].J >> room[i].F;
        room[i].JperF = (double) room[i].J / room[i].F;
    }
}

void work() {
    sort(room, room+N);
    for (int i = 0; i < N; i++) {
        if (M >= room[i].F) {
            ans += room[i].J;
            M -= room[i].F;
        } else {
            ans += room[i].JperF * M;
            break;
        }
    }
}

void output() {
    cout << fixed << setprecision(3) << ans << endl;
}

int main() {
    while (cin >> M >> N && !(M == -1 && N == -1)) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
