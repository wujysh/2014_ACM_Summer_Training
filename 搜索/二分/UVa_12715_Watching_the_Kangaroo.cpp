#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;
typedef long long LL;
const int maxn = 100000 + 10;
#define REP(_,a,b) for(int _ = (a); _ <= (b); _++)
struct seg {
    int L, R;
    seg(int L = 0, int R = 0): L(L), R(R) {}
};
bool cmp1(seg a, seg b) {
    if(a.R != b.R)  return a.R < b.R;
    else return a.L < b.L;
}
bool cmp2(seg a, seg b) {
    if(a.L != b.L)  return a.L < b.L;
    else return a.R < b.R;
}
vector<seg>lft, rgt;

int preLMax[maxn], preRMax[maxn];
int n, m;

int main() {

    int ncase, T = 1;
    cin >> ncase;
    while(ncase--) {
        lft.clear();
        rgt.clear();
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; i++) {
            int L, R;
            scanf("%d%d", &L, &R);
            int mid = (L + R) >> 1;
            lft.push_back(seg(L, mid));
            rgt.push_back(seg(mid, R));
        }

        sort(lft.begin(), lft.end(), cmp1);
        preLMax[lft.size()] = 1e9;
        for(int i = lft.size() - 1; i >= 0; i--) {
            preLMax[i] = min(preLMax[i + 1], lft[i].L);
        }
        sort(rgt.begin(), rgt.end(), cmp2);
        preRMax[0] = rgt[0].R;
        for(int i = 1; i < rgt.size(); i++) {
            preRMax[i] = max(preRMax[i - 1], rgt[i].R);
        }
        printf("Case %d:\n", T++);
        while(m--) {
            int x, ans = 0;
            scanf("%d", &x);
            int L = 0, R = lft.size() - 1;
            while(L <= R) {
                int mid = (L + R) >> 1;
                if(lft[mid].R < x) {
                    L = mid + 1;
                } else {
                    R = mid - 1;
                }
            }
            ans = max(ans, x - preLMax[L]);
            L = 0, R = rgt.size() - 1;
            while(L <= R) {
                int mid = (L + R) >> 1;
                if(rgt[mid].L < x) {
                    L = mid + 1;
                } else {
                    R = mid - 1;
                }
            }
            ans = max(ans, preRMax[R] - x);
            ans = max(ans, 0);
            printf("%d\n", ans);
        }
    }
    return 0;
}
