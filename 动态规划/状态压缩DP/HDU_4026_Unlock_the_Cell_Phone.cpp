#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 6;
const int MAXM = 20;
int n, m;
long long dp[MAXM][1 << 16], ans;

struct Node {
    int x, y, type, index;
    Node() {}
    Node(int _x, int _y, int _type) : x(_x), y(_y), type(_type) {}
} node[MAXN*MAXN];
vector<Node> key;
vector<Node> between[MAXM][MAXM];

void init() {
    key.clear();
    memset(dp, -1, sizeof(dp));
    ans = 0;
}

void input() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int type;
            cin >> type;
            node[i*m+j] = Node(i, j, type);
            if (type == 0) {
                key.push_back(Node(i, j, type));
                node[i*m+j].index = key.size() - 1;
            }
        }
    }
}

int gcd(int a, int b) {
    if (b == 0) return a;
    else return gcd(b, a%b);
}

long long DP(int x, int state) {
    //cout << "DP: " << x << " " << state << endl;
    if (dp[x][state] != -1) return dp[x][state];

    if (state == (1 << x)) {
        return dp[x][state] = 1;
    }

    int preState = state - (1 << x);
    dp[x][state] = 0;
    for (int i = 0; i < key.size(); i++) {
        if ((preState & (1 << i)) && (state & (1 << i))) {
            bool flag = true;
            for (int j = 0; j < between[i][x].size(); j++) {
                Node p = between[i][x][j];
                if (p.type == 1 || (p.type == 0 && !(preState & (1 << p.index)))) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                dp[x][state] += DP(i, preState);
            }
        }
    }
    return dp[x][state];
}

void solve() {
    for (int i = 0; i < key.size(); i++) {
        for (int j = 0; j < key.size(); j++) {
            between[i][j].clear();
            if (i == j) continue;
            int w = gcd(abs(key[i].x-key[j].x), abs(key[i].y-key[j].y));
            int p = (key[j].x-key[i].x) / w, q = (key[j].y-key[i].y) / w;
            for (int k = 1; k < w; k++) {
                int xx = key[i].x + p*k, yy = key[i].y + q*k;
                between[i][j].push_back(node[xx*m+yy]);
            }
        }
    }

    for (int i = 0; i < key.size(); i++) {
        ans += DP(i, (1 << key.size()) - 1);
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> m) {
        init();
        input();
        solve();
    }
    return 0;
}
