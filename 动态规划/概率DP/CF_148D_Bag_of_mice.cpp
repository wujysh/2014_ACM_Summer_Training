#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int MAXN = 1010;
double dp[MAXN][MAXN];
bool visited[MAXN][MAXN];
int w, b;

void init() {
    memset(dp, 0, sizeof(dp));
    memset(visited, false, sizeof(visited));
}

double DP(int i, int j) {
    if (i < 0 || j < 0) return dp[i][j] = 0.0;
    if (visited[i][j]) return dp[i][j];
    visited[i][j] = true;

    if (i == 0 && j > 0) return dp[i][j] = 0.0;
    if (i > 0 && j == 0) return dp[i][j] = 1.0;
    if (i == 0 && j == 0) return dp[i][j] = 0.0;
    if (i+j == 2) return dp[i][j] = i * 1.0 / (i + j);

    double a = i, b = j;
    double temp = a/(a+b-2)*DP(a-1, b-2) + (b-2)/(a+b-2)*DP(a, b-3);
    return dp[i][j] = a/(a+b) + b/(a+b)*((b-1)/(a+b-1)*temp);
}

void output() {
    cout << fixed << setprecision(10) << DP(w, b) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> w >> b) {
        init();
        output();
    }
    return 0;
}
