#include <iostream>
#include <cstring>
#include <string>
using namespace std;

const int MAXN = 30;
int cnt[MAXN], n, k, ans, nCase, no;
string str;

void solve() {
    cin >> n >> k >> str;
    ans = 0;
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < str.length(); i++) {
        if (i > k) {
            cnt[str[i-k-1] - 'A']--;
        }
        if (cnt[str[i] - 'A']) ans++;
        cnt[str[i] - 'A']++;
    }
    cout << "Case " << ++no << ": " << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        solve();
    }
    return 0;
}
