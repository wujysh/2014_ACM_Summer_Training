#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 10010, MAXK = 110;
int sg[MAXN], a[MAXK], k, m, l, h, ans;
bool visited[MAXN];

void calcSG() {
    for (int i = 1; i < MAXN; i++) {
        memset(visited, false, sizeof(visited));
        for (int j = 0; j < k && a[j] <= i; j++) {
            visited[sg[i - a[j]]] = true;
        }
        for (int j = 0; j < MAXN; j++) {
            if (!visited[j]) {
                sg[i] = j;
                break;
            }
        }
    }
/*
    for (int i = 0; i < 100; i++) {
        cout << sg[i] << " ";
    }
    cout << endl;
*/
}

void solve() {
    for (int i = 0; i < k; i++) {
        scanf("%d", &a[i]);
    }
    sort(a, a+k);
    calcSG();

    scanf("%d", &m);
    while (m--) {
        scanf("%d", &l);
        ans = 0;
        for (int i = 0; i < l; i++) {
            scanf("%d", &h);
            ans ^= sg[h];
        }
        if (ans == 0) {
            printf("L");
        } else {
            printf("W");
        }
    }
    printf("\n");
}

int main() {
    while (~scanf("%d", &k) && k) {
        solve();
    }
    return 0;
}
