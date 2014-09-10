#include <iostream>
#include <iomanip>
using namespace std;

const int MAXN = 35;
int n;
double ans;

struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) : x(_x), y(_y) {}
    friend Point operator + (const Point &a, const Point &b) {
		return Point(a.x + b.x, a.y + b.y);
	}
	friend Point operator - (const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y);
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
} a[MAXN][MAXN];

struct Line {
    Point a, b;
    Line() {}
    Line(Point _a, Point _b) : a(_a), b(_b) {}
} h[MAXN], v[MAXN];

double det(const Point &a, const Point &b) {
	return a.x * b.y - a.y * b.x;
}

Point line_make_point(Line a, Line b) {
    double s1 = det(a.a - b.a, b.b - b.a);
    double s2 = det(a.b - b.a, b.b - b.a);
    return (s1 * a.b - s2 * a.a) / (s1 - s2);
}

double calc_area(Point a, Point b, Point c, Point d) {
    double area = 0.0;
    area = det(b, a) + det(c, b) + det(d, c) + det(a, d);
    return area / 2.0;
}

void init() {
    a[0][0] = Point(0, 0);
    a[0][n+1] = Point(0, 1);
    a[n+1][0] = Point(1, 0);
    a[n+1][n+1] = Point(1, 1);
}

void input() {
    double x, y;
    for (int i = 1; i <= n; i++) {  // bottom
        cin >> x;
        a[i][0] = Point(x, 0);
    }
    for (int i = 1; i <= n; i++) {  // top
        cin >> x;
        a[i][n+1] = Point(x, 1);
        v[i] = Line(a[i][0], a[i][n+1]);
    }
    for (int i = 1; i <= n; i++) {  // left
        cin >> y;
        a[0][i] = Point(0, y);
    }
    for (int i = 1; i <= n; i++) {  // right
        cin >> y;
        a[n+1][i] = Point(1, y);
        h[i] = Line(a[0][i], a[n+1][i]);
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[j][i] = line_make_point(h[i], v[j]);
        }
    }
    ans = 0;
    for (int i = 1; i <= n+1; i++) {
        for (int j = 1; j <= n+1; j++) {
            ans = max(ans, calc_area(a[i-1][j-1], a[i-1][j], a[i][j], a[i][j-1]));
        }
    }
    cout << fixed << setprecision(6) << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n && n) {
        init();
        input();
        solve();
    }
    return 0;
}
