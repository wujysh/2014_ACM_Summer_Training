#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 1010;
int sg[MAXN], m, n, p;
bool visited[MAXN];
vector<int> a;

void init() {
    int x = 1, y = 2;
    a.push_back(1);
    a.push_back(2);
    while (y < MAXN) {
        int t = y;
        y = x + y;
        a.push_back(y);
        x = t;
    }

    sg[0] = 0;
    sg[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        memset(visited, false, sizeof(visited));
        for (int j = 0; j < a.size() && a[j] <= i; j++) {
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
    for (int i = 1; i < MAXN; i++) {
        cout << sg[i] << " ";
    }
    cout << endl;
*/
}

int main() {
    init();
    while (~scanf("%d%d%d", &m, &n, &p) && (m || n || p)) {
        if ((sg[m] ^ sg[n] ^ sg[p]) == 0) {
            printf("Nacci\n");
        } else {
            printf("Fibo\n");
        }
    }
    return 0;
}
