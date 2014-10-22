#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 55;
int a[maxn], n;

int main() {
    int T;
    scanf("%d", &T);
    for (int co = 1; co <= T; co++) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        int cnt = 0;
        for (int i = 2; i < n; i++) {
            if (a[i] > a[i - 1] && a[i] > a[i + 1]) {
                cnt++;
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}
