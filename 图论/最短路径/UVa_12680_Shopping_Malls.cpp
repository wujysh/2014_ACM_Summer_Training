#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

const int MAXN = 210;
const double INF = 1e16;
double dist[MAXN][MAXN];
int path[MAXN][MAXN], n, m;
struct Place {
    double h, x, y;
    Place(double h = 0, double x = 0, double y = 0): h(h), x(x), y(y) {}
} P[MAXN];

inline double getDis(int a, int b, char *w) {
    double dis = (P[a].x - P[b].x) * (P[a].x - P[b].x) + (P[a].y - P[b].y) * (P[a].y - P[b].y);
    double hei = (P[a].h - P[b].h) * (P[a].h - P[b].h);
    if (strcmp(w, "walking") == 0) {
        return sqrt(dis);
    }
    if (strcmp(w, "lift") == 0) return 1.0;
    if (strcmp(w, "stairs") == 0) {
        return sqrt(dis + 25 * hei);
    }
    return 3 * sqrt(dis + 25 * hei);
}

void init() {
    for (int i = 0; i <= n; i++) {
        dist[i][i] = 0;
        for (int j = i + 1; j <= n; j++) {
            path[i][j] = path[j][i] = -1;
            dist[i][j] = dist[j][i] = INF;
        }
    }
}

void print(int u, int v) {
    int k = path[u][v];
    if (k == -1) return;
    print(u, k);
    printf("%d ", k - 1);
    print(k, v);
}

int main() {
    int T = 1;
    while (~scanf("%d%d", &n, &m)) {
        init();
        if (!T) puts("");
        for (int i = 1; i <= n; i++) {
            scanf("%lf%lf%lf", &P[i].h, &P[i].x, &P[i].y);
        }
        for (int i = 0; i < m; i++) {
            int a, b;
            char way[20];
            scanf("%d %d %s", &a, &b, way);
            a++;
            b++;
            double dis = getDis(a, b, way);
            if (strcmp(way, "escalator") == 0) {
                if (dist[a][b] > 1)
                    dist[a][b] = 1;
                if (dist[b][a] > dis)
                    dist[b][a] = dis;
            } else {
                if (dist[a][b] > dis)
                    dist[a][b] = dist[b][a] = dis;
            }
        }
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        path[i][j] = k;
                    }
                }
            }
        }
        int q;
        scanf("%d", &q);
        while (q--) {
            int a, b;
            scanf("%d%d", &a, &b);
            a++;
            b++;
            printf("%d ", a - 1);
            print(a, b);
            printf("%d\n", b - 1);
        }
        T = 0;
    }
    return 0;
}
