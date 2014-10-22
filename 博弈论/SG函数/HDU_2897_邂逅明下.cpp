#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 65550;
int sg[MAXN], n, p, q;
bool visited[MAXN];

void calcSG() {
    for (int i = 0; i <= p; i++) {
        sg[i] = 0;
    }

    for (int i = p+1; i <= n; i++) {
        memset(visited, false, sizeof(visited));
        for (int j = p; j <= q && j <= i; j++) {
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

int main() {
    while (~scanf("%d%d%d", &n, &p, &q)) {
        //calcSG();
        //if (sg[n] == 0) {
        int tmp = n % (p + q);
        if (tmp > 0 && tmp <= p) {
            printf("LOST\n");
        } else {
            printf("WIN\n");
        }
    }
    return 0;
}
