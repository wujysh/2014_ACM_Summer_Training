#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

const double eps = 1e-8;
const int MAXN = 1010;
int nCase, n;

int cmp(double x) {
	if (fabs(x) < eps) return 0;
	if (x > 0) return 1;
	return -1;
}

struct point {
	double x, y;
	point() {}
	point(double a, double b) :x(a), y(b) {}
	friend point operator-(const point &a, const point &b) {
		return point(a.x - b.x, a.y - b.y);
	}
	friend bool operator==(const point &a, const point &b) {
		return cmp(a.x - b.x) == 0 && cmp(a.y - b.y) == 0;
	}
	friend bool operator!=(const point &a, const point &b) {
		return cmp(a.x - b.x) != 0 || cmp(a.y - b.y) != 0;
	}
};
vector<point> a;

struct polygon_convex {
	vector <point> P;
	polygon_convex(int Size = 0) {
		P.resize(Size);
	}
} hull[MAXN];

double det(const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}

bool comp_less(const point &a, const point &b) {
	return cmp(a.y - b.y < 0) || cmp(a.y - b.y) == 0 && cmp(a.x - b.x) < 0;
}

bool judge_convex_hull(vector<point> a) {
	polygon_convex res(2 * a.size() + 5);
	sort(a.begin(), a.end(), comp_less);
	a.erase(unique(a.begin(), a.end()), a.end());
	int m = 0;
	for (int i = 0; i < a.size(); i++) {
		while (m > 1 && cmp(det(res.P[m - 1] - res.P[m - 2], a[i] - res.P[m - 2])) <= 0) --m;
		res.P[m++] = a[i];
	}
	int k = m;
	for (int i = int(a.size()) - 2; i >= 0; i--) {
		while (m > k && cmp(det(res.P[m - 1] - res.P[m - 2], a[i] - res.P[m - 2])) <= 0) --m;
		res.P[m++] = a[i];
	}
	res.P.resize(m);
	if (a.size() > 1) res.P.resize(m - 1);

	if (res.P.size() <= 2) return false;
	res.P.push_back(res.P[0]);
	for (int i = 0; i < res.P.size()-1; i++) {
        bool flag = false;
        for (int j = 0; j < a.size(); j++) {
            if (a[j] != res.P[i] && a[j] != res.P[i+1]) {
                if (cmp(det(a[j] - res.P[i], res.P[i+1] - res.P[i])) == 0) {
                    flag = true;
                }
            }
        }
        if (!flag) return false;
	}
	return true;
}

void init() {
    a.clear();
}

void input() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        double x, y;
        cin >> x >> y;
        a.push_back(point(x, y));
    }
}

void solve() {
    if (judge_convex_hull(a)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main() {
    cin >> nCase;
    while (nCase--) {
        init();
        input();
        solve();
    }
    return 0;
}
