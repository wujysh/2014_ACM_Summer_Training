#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 30;
const int INF = 0x3f3f3f3f;
int mp[MAXN], n, nCase;

void init() {
    for (int i = 0; i < MAXN; i++) {
        mp[i] = 0;
    }
}

void input() {
    scanf("%d", &n);
}

int min_dis(int i, int o1, int o2, int o3, int o4, int o5) {
    int ir = i / 5, ic = i % 5;
    int o1r = o1 / 5, o1c = o1 % 5;
    int o2r = o2 / 5, o2c = o2 % 5;
    int o3r = o3 / 5, o3c = o3 % 5;
    int o4r = o4 / 5, o4c = o4 % 5;
    int o5r = o5 / 5, o5c = o5 % 5;

    int ret = INF;
    ret = min(ret, abs(ir-o1r) + abs(ic - o1c));
    ret = min(ret, abs(ir-o2r) + abs(ic - o2c));
    ret = min(ret, abs(ir-o3r) + abs(ic - o3c));
    ret = min(ret, abs(ir-o4r) + abs(ic - o4c));
    ret = min(ret, abs(ir-o5r) + abs(ic - o5c));
    return ret;
}

void solve() {
    if (n <= 5) {
        vector<int> v;
        for (int i = 0; i < n; i++) {
            int x, y, p;
            scanf("%d%d%d", &x, &y, &p);
            v.push_back(x*5+y);
            mp[x*5+y] = 1;
        }
        for (int i = 0; i < 25; i++) {
            if (v.size() == 5) break;
            if (mp[i] == 0) {
                v.push_back(i);
            }
        }
        sort(v.begin(), v.end());
        for (int i = 0; i < 5; i++) {
            if (i) printf(" ");
            printf("%d", v[i]);
        }
        printf("\n");
    } else {
        for (int i = 0; i < n; i++) {
            int x, y, p;
            scanf("%d%d%d", &x, &y, &p);
            mp[x*5+y] = p;
        }

        int min_sum = INF, ans1, ans2, ans3, ans4, ans5;
        for (int off1 = 0; off1 < 21; off1++) {
            for (int off2 = off1+1; off2 < 22; off2++) {
                for (int off3 = off2+1; off3 < 23; off3++) {
                    for (int off4 = off3+1; off4 < 24; off4++) {
                        for (int off5 = off4+1; off5 < 25; off5++) {
                            int tmpsum = 0;
                            for (int i = 0; i < 25; i++) {
                                if (mp[i] == 0) continue;
                                int dis = min_dis(i, off1, off2, off3, off4, off5);
                                tmpsum += dis * mp[i];
                                if (tmpsum > min_sum) {
                                    break;
                                }
                            }
                            if (tmpsum < min_sum) {
                                min_sum = tmpsum;
                                ans1 = off1;ans2 = off2;ans3 = off3;ans4 = off4;ans5 = off5;
                            }
                        }
                    }
                }
            }
        }
        printf("%d %d %d %d %d\n", ans1, ans2, ans3, ans4, ans5);
    }
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
