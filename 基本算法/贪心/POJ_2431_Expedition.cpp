#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 10010;
struct Fuel {
    int pos, amount;
    Fuel() {}
    Fuel(int _pos, int _amount) : pos(_pos), amount(_amount) {}
    bool operator<(const Fuel &b) const {
        return amount < b.amount;
    }
} fuel[MAXN];
int L, P, N;
priority_queue<Fuel> q;

bool cmp(const Fuel &a, const Fuel &b) {
    return a.pos < b.pos;
}

void init() {
    while (!q.empty()) q.pop();
}

void input() {
    for (int i = 0; i < N; i++) {
        cin >> fuel[i].pos >> fuel[i].amount;
    }
    cin >> L >> P;
    for (int i = 0; i < N; i++) {
        fuel[i].pos = L - fuel[i].pos;
    }
}

void solve() {
    sort(fuel, fuel+N, cmp);
    int R = P, cnt = 0, ans = 0;
    while (R < L) {
        while (fuel[cnt].pos <= R && cnt < N) {
            q.push(fuel[cnt++]);
        }
        //cout << cnt << " " << q.size() << endl;
        if (q.empty()) {
            ans = -1;
            break;
        }
        R += q.top().amount;
        q.pop();
        ans++;
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> N) {
        init();
        input();
        solve();
    }
    return 0;
}
