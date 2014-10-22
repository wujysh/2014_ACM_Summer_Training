#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 10010;
int sg[MAXN], n, s, nCase, ans;
bool visited[MAXN];

void calcSG() {
    for (int i = 1; i < MAXN; i++) {
        memset(visited, false, sizeof(visited));
        for (int j = 1; j <= i; j++) {
            visited[sg[i - j]] = true;
        }
        for (int j = 1; j <= i/2; j++) {
            visited[sg[j] ^ sg[i - j]] = true;
        }
        for (int j = 0; j < MAXN; j++) {
            if (!visited[j]) {
                sg[i] = j;
                break;
            }
        }
    }

    for (int i = 1; i <= 1000; i++) {
        cout << sg[i] << " ";
    }
    cout << endl;
}

void solve() {
    scanf("%d", &n);
    ans = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &s);
        //ans ^= sg[s];
        int tmp = s % 4;
        if (tmp == 0) {
            ans ^= s - 1;
        } else if (tmp == 1 || tmp == 2) {
            ans ^= s;
        } else if (tmp == 3) {
            ans ^= s + 1;
        }
    }
    if (ans == 0) {
        printf("Bob\n");
    } else {
        printf("Alice\n");
    }
}

int main() {
    //calcSG();
    scanf("%d", &nCase);
    while (nCase--) {
        solve();
    }
    return 0;
}
