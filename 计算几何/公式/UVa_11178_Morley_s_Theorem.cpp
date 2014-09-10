#include <iostream>
#include <iomanip>
#include <functional>
//#include <cstdio>
#include <cmath>
using namespace std;

const double pi = acos(-1.0);
const double eps = 1e-8;
int nCase;

int cmp(double x) {
	if (fabs(x) < eps) return 0;
	if (x > 0) return 1;
	return -1;
}

inline double sqr(double x) {
	return x * x;
}

struct point {
	double x, y;
	point() {}
	point(double a, double b) :x(a), y(b) {}
	void input() {
		cin >> x >> y;
	}
	void output() {
        cout << fixed << setprecision(6) << x << " " << y;
	}
	friend point operator + (const point &a, const point &b) {
		return point(a.x + b.x, a.y + b.y);
	}
	friend point operator - (const point &a, const point &b) {
		return point(a.x - b.x, a.y - b.y);
	}
	friend bool operator == (const point &a, const point &b) {
		return cmp(a.x - b.x) == 0 && cmp(a.y - b.y) == 0;
	}
	friend point operator * (const point &a, const double &b) {
		return point(a.x * b, a.y * b);
	}
	friend point operator * (const double &a, const point &b) {
		return point(a * b.x, a * b.y);
	}
	friend point operator / (const point &a, const double &b) {
		return point(a.x / b, a.y / b);
	}
	double norm() {
		return sqrt(sqr(x) + sqr(y));
	}
} A, B, C, D, E, F;

double det(const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}
double dot(const point &a, const point &b) {
	return a.x * b.x + a.y * b.y;
}
point rotate(const point &p, double A) {
	double tx = p.x, ty = p.y;
	return point(tx * cos(A) - ty * sin(A), tx * sin(A) + ty * cos(A));
}

double angle(point A, point B) {
    return acos(dot(A, B) / A.norm() / B.norm());
}

point getLineIntersection(point P, point v, point Q, point w) {
    point u = P - Q;
    double t = det(w, u) / det(v, w);
    return P + v*t;
}

point getD(point A, point B, point C) {
    point v1 = C - B;
    double a1 = angle(A-B, v1);
    v1 = rotate(v1, a1/3);

    point v2 = B - C;
    double a2 = angle(A-C, v2);
    v2 = rotate(v2, -a2/3);

    return getLineIntersection(B, v1, C, v2);
}

void solve() {
    A.input();  B.input();  C.input();

    D = getD(A, B, C);
    E = getD(B, C, A);
    F = getD(C, A, B);

    D.output();cout << " ";
    E.output();cout << " ";
    F.output();cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        solve();
    }
	return 0;
}
