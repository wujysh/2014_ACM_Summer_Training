#include <cstring>
#include <cstdio>
using namespace std;

char cur[10], pre[10];
int precnt;

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
        for (int i = 0; i < precnt; i++) {
            printf(" ");
        }
        printf("%s\n", cur);
        strcpy(pre, cur);
    }
    return 0;
}
