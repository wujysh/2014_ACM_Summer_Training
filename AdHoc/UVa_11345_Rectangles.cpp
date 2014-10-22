#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <map>
using namespace std;

const int MAXN = 50;
int nCase, n, cnt, ans;
map<int, map<int, int> > mp;
vector<int> xx, yy;

struct Rect {
    int x1, y1, x2, y2;
} rect[MAXN];

void init() {
    xx.clear();
    yy.clear();
    mp.clear();
    ans = 0;
}

void input() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d%d", &rect[i].x1, &rect[i].y1, &rect[i].x2, &rect[i].y2);
        xx.push_back(rect[i].x1);
        xx.push_back(rect[i].x2);
        yy.push_back(rect[i].y1);
        yy.push_back(rect[i].y2);
    }
}

void solve() {
    sort(xx.begin(), xx.end());
    sort(yy.begin(), yy.end());
    xx.erase(unique(xx.begin(), xx.end()), xx.end());
    yy.erase(unique(yy.begin(), yy.end()), yy.end());

    for (int i = 0; i < n; i++) {
        int xx1 = lower_bound(xx.begin(), xx.end(), rect[i].x1) - xx.begin();
        int yy1 = lower_bound(yy.begin(), yy.end(), rect[i].y1) - yy.begin();
        int xx2 = lower_bound(xx.begin(), xx.end(), rect[i].x2) - xx.begin();
        int yy2 = lower_bound(yy.begin(), yy.end(), rect[i].y2) - yy.begin();

        for (int j = xx1; j < xx2; j++) {
            for (int k = yy1; k < yy2; k++) {
                mp[j][k]++;
            }
        }
    }
/*
    for (int i = 0; i < xx.size(); i++) {
        for (int j = 0; j < yy.size(); j++) {
            cout << mp[i][j] << " ";
        }
        cout << endl;
    }
*/
    for (int i = 0; i < xx.size()-1; i++) {
        for (int j = 0; j < yy.size()-1; j++) {
            if (mp[i][j] == n) {
                ans += (xx[i+1] - xx[i]) * (yy[j+1] - yy[j]);
            }
        }
    }
    printf("Case %d: %d\n", ++cnt, ans);
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        init();
        input();
        solve();
    }
    return 0;
}
