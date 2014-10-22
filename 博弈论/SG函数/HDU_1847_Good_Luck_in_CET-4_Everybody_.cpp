#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 1010;
int sg[MAXN], n;
vector<int> a;

void init() {
    for (int i = 0; i < MAXN; i++) {
        sg[i] = -1;
    }
    int x = 1;
    a.clear();
    for (int i = 0; i < 10; i++) {
        a.push_back(x);
        sg[x] = 1;
        x *= 2;
    }
    for (int i = 1; i <= 1000; i++) {
        if (sg[i] > 0) continue;
        bool flag = true;
        for (int j = 0; j < a.size() && a[j] < i; j++) {
            if (sg[i - a[j]] == 0) {
                sg[i] = 1;
                flag = false;
                break;
            }
        }
        if (flag) sg[i] = 0;
    }
/*
    for (int i = 1; i <= 1000; i++) {
        cout << sg[i] << " ";
    }
    cout << endl;
*/
}

int main() {
    /*
    init();
    while (~scanf("%d", &n)) {
        if (sg[n] == 1) {
            printf("Kiki\n");
        } else {
            printf("Cici\n");
        }
    }
    */
    while (~scanf("%d", &n)) {
        if (n % 3 != 0) {
            printf("Kiki\n");
        } else {
            printf("Cici\n");
        }
    }
    return 0;
}
