/*
#include <algorithm>
#include <iostream>
#include <complex>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <cmath>
using namespace std;

typedef complex <double> Point;
typedef pair <Point, Point> Halfplane;
const double EPS = 1e-10;
const double INF = 10000;

inline int sgn(double n) {
    return fabs(n) < EPS ? 0 : (n < 0 ? -1 : 1);
}
inline double cross(Point a, Point b) {
    return (conj(a) * b).imag();
}
inline double dot(Point a, Point b) {
    return (conj(a) * b).real();
}
inline bool satisfy(Point a, Halfplane p) {
    return sgn(cross(a - p.first, p.second - p.first)) <= 0;
}

Point crosspoint(const Halfplane &a, const Halfplane &b) {
    double k = cross(b.first - b.second, a.first - b.second);
    k = k / (k - cross(b.first - b.second, a.second - b.second));
    return a.first + (a.second - a.first) * k;
}

bool cmp(const Halfplane &a, const Halfplane &b) {
    int res = sgn(arg(a.second - a.first) - arg(b.second - b.first));
    return res == 0 ? satisfy(a.first, b) : res < 0;
}

vector <Point> halfplaneIntersection(vector <Halfplane> v) {
    sort(v.begin(), v.end(), cmp);
    ///
    for (int i = 0; i < v.size(); i++) {
        cout << v[i].first << " " << v[i].second << endl;
    }
    ///
    deque <Halfplane> q;
    deque <Point> ans;
    q.push_back(v[0]);
    for (int i = 1; i < v.size(); i++) {
        if (sgn(arg(v[i].second - v[i].first) - arg(v[i-1].second - v[i-1].first)) == 0) {
            continue;
        }
        while (ans.size() > 0 && !satisfy(ans.back(), v[i])) {
            ans.pop_back();
            q.pop_back();
        }
        while (ans.size() > 0 && !satisfy(ans.front(), v[i])) {
            ans.pop_front();
            q.pop_front();
        }
        ans.push_back(crosspoint(q.back(), v[i]));
        //cout << ans.back() << endl;
        q.push_back(v[i]);
    }
    while (ans.size() > 0 && !satisfy(ans.back(), q.front())) {
        ans.pop_back();
        q.pop_back();
    }
    while (ans.size() > 0 && !satisfy(ans.front(), q.back())) {
        ans.pop_front();
        q.pop_front();
    }
    ans.push_back(crosspoint(q.back(), q.front()));
    ///
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i].real() << " " << ans[i].imag() << endl;
    }
    ///
    return vector <Point>(ans.begin(), ans.end());
}

double x, y, area;
string state;
vector <Halfplane> plane;
vector <Point> polygon;
Point a, b, c, d;

void init() {
    plane.clear();
    plane.push_back(make_pair((0.0, 0.0), (10.0, 0.0)));
    plane.push_back(make_pair((10.0, 0.0), (10.0, 10.0)));
    plane.push_back(make_pair((10.0, 10.0), (0.0, 10.0)));
    plane.push_back(make_pair((0.0, 10.0), (0.0, 0.0)));
    a.real() = 0;  a.imag() = 0;
    area = 100.0;
    polygon = halfplaneIntersection(plane);
    for (int i = 0; i < polygon.size(); i++) {
        cout << polygon[i].real() << " " << polygon[i].imag() << endl;
    }
}

void work() {
    c.real() = (a.real() + b.real()) / 2.0;
    c.imag() = (a.imag() + b.imag()) / 2.0;
    d.real() = c.real() - b.imag() + a.imag();
    d.imag() = c.imag() + b.real() - a.real();
    if (state == "Same") {
        area = 0.0;
    } else if (state == "Colder") {
        plane.push_back(make_pair(c, d));
    } else if (state == "Hotter") {
        plane.push_back(make_pair(d, c));
    }
    polygon = halfplaneIntersection(plane);

    a = b;
}

void output() {
    cout << fixed << setprecision(2) << area << endl;
}

int main() {
    ios::sync_with_stdio(false);
    init();
    while (cin >> b.real() >> b.imag() >> state) {
        work();
        output();
    }
    return 0;
}
*/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps = 1e-10;

struct point {
    double x, y;
    point() {}
    point(double xx, double yy): x(xx), y(yy) {}
} p[110], tp[110], cur, pre;

int n, m;

void getline(point p1, point p2, double &a, double &b, double &c) { //获得中垂线
    point p3 = point( (p1.x + p2.x) / 2, (p1.y + p2.y) / 2 );
    a = p1.x - p2.x;
    b = p1.y - p2.y;
    c = - a * p3.x - b * p3.y;
}

point intersect(point p1, point p2, double a, double b, double c) {
    double u = fabs(a * p1.x + b * p1.y + c);
    double v = fabs(a * p2.x + b * p2.y + c);
    point ans;
    ans.x = (v * p1.x + u * p2.x) / (u + v);
    ans.y = (v * p1.y + u * p2.y) / (u + v);
    return ans;
}

void cut(double a, double b, double c) { //切割
    int i, tm = 0;
    for (i = 1; i <= m; i++) {
        if (a * p[i].x + b * p[i].y + c > eps)
            tp[++tm] = p[i];
        else {
            if ( a * p[i - 1].x + b * p[i - 1].y + c > eps)
                tp[++tm] = intersect(p[i - 1], p[i], a, b, c);
            if ( a * p[i + 1].x + b * p[i + 1].y + c > eps)
                tp[++tm] = intersect(p[i], p[i + 1], a, b, c);
        }
    }

    for (i = 1; i <= tm; i++)
        p[i] = tp[i];
    p[0] = p[tm];
    p[tm + 1] = p[1];
    m = tm;
}

double calcArea(int n, point *p) { //多边形面积
    int i;
    double s = 0;
    p[n + 1] = p[1];
    for (i = 1; i <= n; i++)
        s += p[i].x * p[i + 1].y - p[i].y * p[i + 1].x;
    return fabs(s) / 2;
}

char str[11];

int main() {
    bool flag = 0;
    double a, b, c;
    pre = point(0, 0);
    m = n = 4;
    p[1] = point(0, 0);
    p[2] = point(0, 10);
    p[3] = point(10, 10);
    p[4] = point(10, 0);
    p[5] = p[1];
    p[0] = p[4];
    while ( ~scanf("%lf%lf%s", &cur.x, &cur.y, str) ) {
        getline(pre, cur, a, b, c);
        if (str[0] == 'C') {
            if (a * pre.x + b * pre.y + c < -eps) {
                a = -a;
                b = -b;
                c = -c;
            }
        } else if (str[0] == 'H') {
            if (a * cur.x + b * cur.y + c < -eps) {
                a = -a;
                b = -b;
                c = -c;
            }
        } else flag = 1; //注意same以后，每次答案都为0；
        if (flag) {
            puts("0.00");
            continue;
        }
        cut(a, b, c);
        printf("%.2f\n", calcArea(m, p));
        pre = cur;
    }
    return 0;
}
