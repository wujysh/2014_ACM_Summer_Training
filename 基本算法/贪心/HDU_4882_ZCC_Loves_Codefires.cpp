#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Problem {
    int e, k;
    Problem() {}
    bool operator<(const Problem &b) const {
        return e * b.k < k * b.e;
    }
};
vector<Problem> problem;
int n;

void init() {
    problem.clear();
    problem.resize(n);
}

void input() {
    for (int i = 0; i < n; i++) {
        cin >> problem[i].e;
    }
    for (int i = 0; i < n; i++) {
        cin >> problem[i].k;
    }
}

void solve() {
    sort(problem.begin(), problem.end());
    long long time = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        time += problem[i].e;
        ans += time * problem[i].k;
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n) {
        init();
        input();
        solve();
    }
    return 0;
}
