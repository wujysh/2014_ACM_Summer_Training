#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 55;
const int INF = 110;
const double eps = 1e-8;

int n, nCase;

struct Point {
    int x, y, no;
    Point() {}
    Point(int _x, int _y) : x(_x), y(_y) {}
    friend Point operator-(const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y);
	}
	double norm() {
		return sqrt(x*x + y*y);
	}
} point[MAXN], pivot;

double det(const Point &a, const Point &b) {
	return a.x * b.y - a.y * b.x;
}

int dcmp(double x) {
	if (fabs(x) < eps) return 0;
	if (x > 0) return 1;
	return -1;
}

bool cmp_clockwise(const Point &a, const Point &b) {
	double t = det(a - pivot, b - pivot);
	return dcmp(t) > 0 || (dcmp(t) == 0 && dcmp((pivot - a).norm() - (pivot - b).norm()) < 0);
}

void init() {
    pivot = Point(INF, INF);
}

void input() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> point[i].no >> point[i].x >> point[i]. y;
        if (point[i].y < pivot.y || (point[i].y == pivot.y && point[i].x < pivot.x)) {
            pivot.x = point[i].x;
            pivot.y = point[i].y;
        }
    }
}

void solve() {
    sort(point, point+n, cmp_clockwise);
    cout << n << " " << point[0].no;
    for (int i = 1; i < n; i++) {
        cout << " ";
        pivot = point[i-1];
        sort(point+i, point+n, cmp_clockwise);
        cout << point[i].no;
    }
    cout << endl;
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
