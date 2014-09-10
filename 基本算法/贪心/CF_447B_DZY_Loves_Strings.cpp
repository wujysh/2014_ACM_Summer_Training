#include <iostream>
#include <string>
using namespace std;

int k, w[26], maxw, sum, l, ans;
string s;

void init() {
    maxw = 0;
    sum = 0;
    ans = 0;
}

void input() {
    cin >> k;
    for (int i = 0; i < 26; i++) {
        cin >> w[i];
        if (w[i] > maxw) {
            maxw = w[i];
        }
    }
}

void work() {
    l = s.length();
    for (int i = 0; i < l; i++) {
        sum += w[s[i] - 'a'];
        ans += w[s[i] - 'a'] * (i+1);
    }
    for (int i = 1; i <= k; i++) {
        //cout << maxw << " " << l+1 << " " << sum << endl;
        if (maxw * (l+1) >= sum + maxw) {  // insert at back
            ans += maxw * (l+1);
            sum += maxw;
        } else {  // insert at front
            ans += sum + maxw;
            sum += maxw;
        }
        l++;
    }
}

void output() {
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> s) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
