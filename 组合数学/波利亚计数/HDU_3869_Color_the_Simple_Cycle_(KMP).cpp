//#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 100010;
const int MOD = 1000000007;
int nCase, N, C, v[MAXN], vv[MAXN << 1], e[MAXN], ee[MAXN << 1], cnt;
long long ans;
bool visited[2][MAXN];

void KMP(int pattern[], int text[], int type) {
    vector<int> next(N+1, 0);
    for (int i = 1; i < N; i++) {
        int j = i;
        while (j > 0) {
            j = next[j];
            if (pattern[j] == pattern[i]) {
                next[i+1] = j + 1;
                break;
            }
        }
    }

    for (int i = 0, j = 0; i < 2*N; i++) {
        if (j < N && text[i] == pattern[j]) {
            j++;
        } else {
            while (j > 0) {
                j = next[j];
                if (text[i] == pattern[j]) {
                    j++;
                    break;
                }
            }
        }
        if (j == N) {
            visited[type][i-N+1] = true;
        }
    }
}

long long pow_mod(int a, int r, int MOD) {
    long long ans = 1, t = a;
    while (r) {
        if (r & 1) {
            ans = ans * t % MOD;
        }
        t = t * t % MOD;
        r >>= 1;
    }
    return ans;
}

int gcd(int a, int b) {
    return (b == 0) ? a : gcd(b, a%b);
}

void init() {
    memset(visited, false, sizeof(visited));
    ans = cnt = 0;
}

void input() {
    //cin >> N >> C;
    scanf("%d%d", &N, &C);
    for (int i = 0; i < N; i++) {
        //cin >> v[i];
        scanf("%d", &v[i]);
        vv[i] = vv[i+N] = v[i];
    }
    for (int i = 0; i < N; i++) {
        //cin >> e[i];
        scanf("%d", &e[i]);
        ee[i] = ee[i+N] = e[i];
    }
}

void solve() {
    KMP(v, vv, 0);
    KMP(e, ee, 1);

    for (int i = 1; i <= N; i++) {
        if (visited[0][i] && visited[1][i]) {
            ans += pow_mod(C, gcd(i, N), MOD);
            ans %= MOD;
            cnt++;
        }
    }
    //cout << ans * pow_mod(cnt, MOD-2, MOD) % MOD << endl;
    printf("%I64d\n", ans * pow_mod(cnt, MOD-2, MOD) % MOD);
}

int main() {
    //ios::sync_with_stdio(false);
    //cin >> nCase;
    scanf("%d", &nCase);
    while (nCase--) {
        init();
        input();
        solve();
    }
    return 0;
}
