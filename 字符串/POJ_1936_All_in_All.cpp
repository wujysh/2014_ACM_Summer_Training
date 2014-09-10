#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 100010;
char str1[MAXN], str2[MAXN];

void solve() {
    int i = 0, j = 0;
    for ( ;i < strlen(str1); i++) {
        for ( ; j < strlen(str2); j++) {
            if (str1[i] == str2[j]) {
                i++;
            }
        }
    }
    if (i == strlen(str1)+1) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
}

int main() {
    while (~scanf("%s %s", str1, str2)) {
        solve();
    }
    return 0;
}
