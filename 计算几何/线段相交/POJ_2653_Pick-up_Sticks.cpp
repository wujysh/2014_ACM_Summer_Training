//#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 100010;
vector <int> ans;
int n;

struct Line {
	double x1, y1, x2, y2, u, v;
	Line(double x10 = 0, double y10 = 0, double x20 = 0, double y20 = 0) {
		x1 = x10;  y1 = y10;  x2 = x20;  y2 = y20;
		u = x2 - x1;  v = y2 - y1;
	}
} line[MAXN];

double cross(Line l1, Line l2) {
	return(l1.u*l2.v - l2.u*l1.v);
}

bool fastTest(Line l1, Line l2) {
	double left1 = min(l1.x1, l1.x2), left2 = min(l2.x1, l2.x2);
	double right1 = max(l1.x1, l1.x2), right2 = max(l2.x1, l2.x2);
	double top1 = max(l1.y1, l1.y2), top2 = max(l2.y1, l2.y2);
	double bottom1 = min(l1.y1, l1.y2), bottom2 = min(l2.y1, l2.y2);
	if (right1 < left2 || left1 > right2 || top1 < bottom2 || bottom1 > top2) return true;
	return false;
}

bool furtherTest(Line l1, Line l2) {  // l1:AB  l2:CD
	Line l3 = Line(l1.x1, l1.y1, l2.x1, l2.y1);  // l3:AC
	Line l4 = Line(l1.x1, l1.y1, l2.x2, l2.y2);  // l4:AD
	Line l5 = Line(l2.x1, l2.y1, l1.x1, l1.y1);  // l5:CA
	Line l6 = Line(l2.x1, l2.y1, l1.x2, l1.y2);  // l6:CB
	if (cross(l3, l1)*cross(l1, l4) >= 0 && cross(l5, l2)*cross(l2, l6) >= 0) return false;
	return true;
}

bool judge(Line l1, Line l2) {
	// fast test
	if (!fastTest(l1, l2)) {
		// further test
		if (!furtherTest(l1, l2)) {
			return false;
		}
	}
	return true;
}

void init() {
    ans.clear();
}

void input() {
    for (int i = 0; i < n; i++) {
        double x1, y1, x2, y2;
        //cin >> x1 >> y1 >> x2 >> y2;
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        line[i] = Line(x1, y1, x2, y2);
    }
}

void work() {
    for (int i = 0; i < n; i++) {
        bool flag = false;
        for (int j = i + 1; j < n; j++) {
            if (!judge(line[i], line[j])) {
                flag = true;
                break;
            }
        }
        if (!flag) ans.push_back(i + 1);
    }
}

void output() {
    //cout << "Top sticks:";
    printf("Top sticks:");
    for (int i = 0; i < ans.size(); i++) {
        //if (i) cout << ",";
        if (i) printf(",");
        //cout << " " << ans[i];
        printf(" %d", ans[i]);
    }
    //cout << "." << endl;
    printf(".\n");
}

int main() {
    //ios::sync_with_stdio(false);
	//while (cin >> n && n) {
	while (~scanf("%d", &n) && n) {
		init();
		input();
		work();
		output();
	}
	return 0;
}
