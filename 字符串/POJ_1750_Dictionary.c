#include <string.h>
#include <stdio.h>

char cur[15], pre[15];
int precnt, i;

int main() {
    while (~scanf("%s", cur) && cur != "") {
        int cnt = 0;
        for ( ; cnt < strlen(pre) && cnt < strlen(cur); cnt++) {
            if (cur[cnt] != pre[cnt]) {
                break;
            }
        }
        if (cnt > precnt) {
            precnt++;
        } else {
            precnt = cnt;
        }
        for (i = 0; i < precnt; i++) {
            //printf(" ");
            putchar(' ');
        }
        for (i = 0; i < strlen(cur); i++) {
            putchar(cur[i]);
        }
        putchar('\n');
        //printf("%s\n", cur);
        strcpy(pre, cur);
    }
    return 0;
}
