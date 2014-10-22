#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 5;
int a[MAXN], sum, ans, n;

void init() {
    sum = 0;
    ans = 0;
}

void input() {
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
}

inline int mod(int x) {
    while (x > 1024) {
        x -= 1024;
    }
    return x;
}

void solve() {
    if (n <= 3) {  // 有2个不确定时，一定可以调整，最终得到1024
        printf("1024\n");
        return;
    }
    if (n == 4) {  // 有1个不确定时，分两种情况
        // 当前面4个中有3个数能组成1024的倍数，剩下那个数与最后一个一定可以调整出1024的倍数，最后得到1024
        for (int i = 0; i < 4; i++) {
            if ((sum - a[i]) % 1024 == 0) {
                printf("1024\n");
                return;
            }
        }
        // 当前面4个中没有3个数能组成1024的倍数，最后一个数只能用来与前面的2个数，凑1024的倍数，枚举剩下的2个数算被偷后的最终结果
        for (int i = 0; i < 4; i++) {
            for (int j = i+1; j < 4; j++) {
                ans = max(ans, mod(a[i]+a[j]));
            }
        }
    }
    if (n == 5) {  // 5个数都确定时，枚举3个数凑1024的倍数，找不到答案为0，找到算被偷后的最终结果
        for (int i = 0; i < 5; i++) {
            for (int j = i+1; j < 5; j++) {
                if ((sum - a[i] - a[j]) % 1024 == 0) {
                    ans = max(ans, mod(a[i]+a[j]));
                }
            }
        }
    }

    printf("%d\n", ans);
}

int main() {
    while (~scanf("%d", &n)) {
        init();
        input();
        solve();
    }
    return 0;
}
