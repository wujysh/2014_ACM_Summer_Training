#include <iostream>
#include <cstring>
#include <string>
using namespace std;

const int MAXN = 5100;
string line;
long long dp[MAXN], ans;
int nCase, nCnt;

void init() {
    nCnt++;
    ans = 1;
}

void input() {
    getline(cin, line);
}

void work() {
    int i = 0;
    while (i < line.size() - 1) {
        if (!(line[i] == 'h' && line[i+1] == 'e')) {
            i++;
            continue;
        }
        int cnt = 0;
        while (line[i] == 'h' && line[i+1] == 'e') {
            i += 2;
            cnt++;
        }
        ans *= dp[cnt];
        ans %= 10007;
    }
}

void output() {
    cout << "Case " << nCnt << ": ";
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);

    memset(dp, 0, sizeof(dp));
    dp[0] = dp[1] = 1;
    for (int i = 2; i < 5050; i++) {
        dp[i] = dp[i-1] + dp[i-2];
        dp[i] %= 10007;
    }

    cin >> nCase;
    cin.ignore();
    while (nCase--) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
