#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

char str[12][5500], S[110];
int nCase, n, cnt;

void init() {
    strcpy(str[1], "L");
    for (int i = 2; i <= 10; i++) {
        strcpy(str[i], str[i-1]);
        int len = strlen(str[i]);
        strcat(str[i], "L");
        for (int j = len-1; j >= 0; j--) {
            if (str[i][j] == 'L') {
                strcat(str[i], "R");
            } else if (str[i][j] == 'R') {
                strcat(str[i], "L");
            }
        }
    }
}

int main() {
    scanf("%d", &nCase);
    init();
    while (nCase--) {
        scanf("%d %s", &n, S);
        if (n >= 10) n = 10;
        if (strstr(str[n], S)!=NULL) {
            printf("Case %d: Yes\n", ++cnt);
        } else {
            printf("Case %d: No\n", ++cnt);
        }
    }
    return 0;
}
