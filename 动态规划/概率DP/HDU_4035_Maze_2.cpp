#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 10010;
const double eps = 1e-10;  //1e-8 WA
int nCase, N, cnt;
double A[MAXN], B[MAXN], C[MAXN], K[MAXN], E[MAXN], ans;
vector<int> graph[MAXN];

void init() {
    for (int i = 1; i <= N; i++) {
        graph[i].clear();
    }
}

void input() {
    //cin >> N;
    scanf("%d", &N);
    for (int i = 0; i < N - 1; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        //cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d%d", &K[i], &E[i]);
        //cin >> K[i] >> E[i];
        K[i] = K[i] / 100;
        E[i] = E[i] / 100;
    }
}

void DP(int x, int father) {
    //cout << x << " " << father << endl;
    double childA = 0, childB = 0, childC = 0;
    double a = 1 - K[x] - E[x];
    int m = graph[x].size();

    if (x == 1 || m > 1) {
        for (int i = 0; i < m; i++) {
            if (graph[x][i] != father) {
                DP(graph[x][i], x);
                childA += A[graph[x][i]];
                childB += B[graph[x][i]];
                childC += C[graph[x][i]];
            }
        }
        A[x] = (K[x] + a / m * childA) / (1 - a / m * childB);
        B[x] = a / m / (1 - a / m * childB);
        C[x] = (a / m * childC + a) / (1 - a / m * childB);
    } else {
        A[x] = K[x];
        B[x] = C[x] = a;
    }
    //cout << A[x] << " " <<  B[x] << " " << C[x] << endl;
}

void solve() {
    DP(1, 0);
    //cout << A[1] << endl;
    if (fabs(A[1] - 1) < eps) {
        ans = -1;
    } else {
        ans = C[1] / (1 - A[1]);
    }

    //cout << "Case " << ++cnt << ": ";
    printf("Case %d: ", ++cnt);
    if (ans == -1) {
        //cout << "impossible" << endl;
        printf("impossible\n");
    } else {
        printf("%.6lf\n", ans);
        //cout << fixed << setprecision(6) << ans << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        init();
        input();
        solve();
    }
    return 0;
}
