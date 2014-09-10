//#include <iostream>
//#include <iomanip>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 10010;
const double eps = 1e-10;
int T, N, cnt;
double A[MAXN], B[MAXN], C[MAXN], K[MAXN], E[MAXN], ans;
vector<vector<int> > graph;

void init() {
    cnt++;
    graph.clear();
}

void input() {
    scanf("%d", &N);
    //cin >> N;
    graph.resize(N+1);

    for (int i = 0; i < N-1; i++) {
        int X, Y;
        scanf("%d%d", &X, &Y);
        //cin >> X >> Y;
        graph[X].push_back(Y);
        graph[Y].push_back(X);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%lf%lf", &K[i], &E[i]);
        //cin >> K[i] >> E[i];
        K[i] /= 100;
        E[i] /= 100;
    }
}

void DP(int father, int x) {
    //cout << "DP: " << father << " " << x << endl;

    double childA = 0, childB = 0, childC = 0;
    double a = 1 - K[x] - E[x], m = graph[x].size();

    if (x == 1 || graph[x].size() > 1) {  // not leaf node
        for (int i = 0; i < graph[x].size(); i++) {
            if (graph[x][i] != father) {
                DP(x, graph[x][i]);
                childA += A[graph[x][i]];
                childB += B[graph[x][i]];
                childC += C[graph[x][i]];
            }
        }
        //cout << "Child: " << childA << " " << childB << " " << childC << endl;
        A[x] = (K[x] + a/m*childA) / (1 - a/m*childB);
        B[x] = a/m / (1 - a/m*childB);
        C[x] = (a/m*childC + a) / (1 - a/m*childB);

    } else {  // leaf node
        A[x] = K[x];  B[x] = C[x] = a;
        //cout << "Leaf:  " << A[x] << " " << B[x] << " " << C[x] << endl;
    }
}

void work() {
    DP(0, 1);
    if (fabs(A[1] - 1) < eps) {
        ans = -1;
    } else {
        ans = C[1] / (1 - A[1]);
    }
    //cout << A[1] << " " << B[1] << " " << C[1] << endl;
}

void output() {
    printf("Case %d: ", cnt);
    //cout << "Case " << cnt << ": ";
    if (ans == -1) {
        printf("impossible\n");
        //cout << "impossible" << endl;
    } else {
        printf("%.6f\n", ans);
        //cout << fixed << setprecision(6) << ans << endl;
    }
}

int main() {
    //ios::sync_with_stdio(false);
    //cin >> T;
    scanf("%d", &T);
    while (T--) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
