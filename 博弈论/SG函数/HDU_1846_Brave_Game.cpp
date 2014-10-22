#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 1010;
int sg[MAXN], nCase, n, m;
bool visited[MAXN];

void calcSG() {
    for (int i = 1; i <= n; i++) {
        memset(visited, false, sizeof(visited));
        for (int j = 1; j <= m && j <= i; j++) {
            visited[sg[i - j]] = true;
        }
        for (int j = 0; j <= n; j++) {
            if (!visited[j]) {
                sg[i] = j;
                break;
            }
        }
    }
/*
    for (int i = 0; i <= n; i++) {
        cout << sg[i] << " ";
    }
    cout << endl;
*/
}

void solve() {
    scanf("%d%d", &n, &m);
    //calcSG();
    //if (sg[n] == 0) {
    if (n % (m+1) == 0) {
        printf("second\n");
    } else {
        printf("first\n");
    }
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        solve();
    }
    return 0;
}
