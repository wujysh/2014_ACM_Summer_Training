#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <set>
using namespace std;

const int MAXN = 30;
const int M = 1300;
const double EPS = 1e-9;
int n, nCase, cnt, cntCase;
double graph[M][M], dis[M];
bool visited[M];

int dcmp(double k) {
    return k < -EPS ? -1 : k > EPS ? 1 : 0;
}

inline double sqr(double x) {
	return x * x;
}
inline double mysqrt(double n) {
    return sqrt(max(0.0, n));
}

struct Point {
	double x, y;
	Point() {}
	Point(double a, double b) :x(a), y(b) {}
	friend bool operator < (const Point &a, const Point &b) {
		if (dcmp(a.x-b.x) == 0) {
            return a.y + EPS < b.y;
		} else {
            return a.x + EPS < b.x;
		}
	}
	friend Point operator + (const Point &a, const Point &b) {
		return Point(a.x + b.x, a.y + b.y);
	}
	friend Point operator - (const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y);
	}
	friend bool operator == (const Point &a, const Point &b) {
		return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
	}
	friend Point operator * (const Point &a, const double &b) {
		return Point(a.x * b, a.y * b);
	}
	friend Point operator * (const double &a, const Point &b) {
		return Point(a * b.x, a * b.y);
	}
	friend Point operator / (const Point &a, const double &b) {
		return Point(a.x / b, a.y / b);
	}
	double norm() {
		return sqrt(sqr(x) + sqr(y));
	}
} point[M];

struct Circle {
    Point p;
    double r;
    Circle() {}
    Circle(double _x, double _y, double _r) : p(_x, _y), r(_r) {}
} circle[MAXN];

Point rotate(const Point &p, double cost, double sint) {
    double x = p.x, y = p.y;
    return Point(x*cost - y*sint, x*sint + y*cost);
}

pair<Point, Point> crosspoint(Point ap, double ar, Point bp, double br) {
    double d = (ap - bp).norm();
    double cost = (ar*ar + d*d - br*br) / (2*ar*d);
    double sint = sqrt(1. - cost*cost);
    Point v = (bp - ap) / (bp - ap).norm() * ar;
    return make_pair(ap + rotate(v, cost, -sint), ap + rotate(v, cost, sint));
}

void circle_cross_line(Point a, Point b, Point o, double r, Point ret[], int &num) {
    double x0 = o.x, y0 = o.y;
    double x1 = a.x, y1 = a.y;
    double x2 = b.x, y2 = b.y;
    double dx = x2 - x1, dy = y2 - y1;
    double A = dx*dx + dy*dy;
    double B = 2*dx*(x1 - x0) + 2*dy*(y1 - y0);
    double C = sqr(x1 - x0) + sqr(y1 - y0) - sqr(r);
    double delta = B*B - 4*A*C;
    num = 0;
    if (dcmp(delta) >= 0) {
        double t1 = (-B - mysqrt(delta)) / (2*A);
        double t2 = (-B + mysqrt(delta)) / (2*A);
        if (dcmp(t1 - 1) <= 0 && dcmp(t1) >= 0) {
            ret[num++] = Point(x1 + t1*dx, y1 + t1*dy);
        }
        if (dcmp(t2 - 1) <= 0 && dcmp(t2) >= 0) {
            ret[num++] = Point(x1 + t2*dx, y1 + t2*dy);
        }
    }
}

void input() {
    scanf("%d",&n);
    for (int i = 0; i < n; i++) {
        double x, y, r;
        scanf("%lf%lf%lf",&x,&y,&r);
        circle[i] = Circle(x, y, r);
        point[i] = Point(x, y);
    }
}

void SPFA(int u) {
    memset(visited, false, sizeof(visited));
    queue<int> q;
    q.push(u);
    visited[u] = true;
    dis[u] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        visited[cur] = false;
        for (int i = 0; i < cnt; i++) {
            if (dis[i] > dis[cur] + graph[cur][i]+EPS) {
                dis[i] = dis[cur] + graph[cur][i];
                if (!visited[i]) {
                    q.push(i);
                    visited[i] = true;
                }
            }
        }
    }
}

void init() {
    for (int i = 0; i < M; i++) {
        dis[i] = 1e18;
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            graph[i][j] = 1e18;
        }
    }
}

void solve() {
    cnt = n;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            double d = (circle[i].p-circle[j].p).norm();
            if (dcmp(d - circle[i].r-circle[j].r) <= 0 && dcmp(d - fabs(circle[i].r-circle[j].r) >= 0)){
                pair<Point, Point> cross = crosspoint(circle[i].p, circle[i].r, circle[j].p, circle[j].r);
                if (!(cross.first == cross.second)) {
                    point[cnt++] = cross.first;
                    point[cnt++] = cross.second;
                } else {
                    point[cnt++] = cross.first;
                }
                graph[i][j] = graph[j][i] = (circle[i].p - circle[j].p).norm();
            } else if (dcmp(d - fabs(circle[i].r-circle[j].r) < 0)) {
                graph[i][j] = graph[j][i] = (circle[i].p - circle[j].p).norm();
            }
        }
    }
    for (int i = 0; i < cnt; i++) {
        for (int j = i+1; j < cnt; j++) {
            set<Point> split;
            for (int k = 0; k < n; k++) {
                Point ret[5];
                int num;
                circle_cross_line(point[i], point[j], circle[k].p, circle[k].r, ret, num);
                for (int l = 0; l < num; l++) {
                    split.insert(ret[l]);
                }
            }
            if (split.empty()) continue;
            set<Point>::iterator tmp = split.begin();
            set<Point>::iterator it = split.begin();
            bool flag1 = true;
            for (it++ ; it != split.end(); it++) {
                Point mid = (*tmp + *it) / 2;
                bool flag = false;
                for (int k = 0; k < n; k++) {
                    if (dcmp((mid - circle[k].p).norm()-circle[k].r) <= 0) {
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    flag1 = false;
                    break;
                }
                tmp = it;
            }
            if (flag1) {
                graph[i][j] = graph[j][i] = (point[i] - point[j]).norm();
            }
        }
    }
    SPFA(0);
    printf("Case %d: ",++cntCase);
    if (dis[n-1] == 1e18) {
        printf("No such path.\n");
    } else {
        printf("%.4f\n",dis[n-1]);
    }
}

int main() {
    scanf("%d",&nCase);
    while (nCase--) {
        init();
        input();
        solve();
    }
    return 0;
}
