#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 105;

int G[maxn][maxn], n;

void input() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &G[i][j]);
}

int judge() {
    int ans = n * (n - 1);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            for(int k = 0; k < n; k++) {
                if(i != j && i != k && j != k && G[i][k] + G[k][j] < G[i][j])  return -1;
                if(i != j && i != k && j != k && G[i][k] + G[k][j] == G[i][j]) {
                    ans--;
                    break;
                }
            }
    return ans;
}

int main() {
    int T;
    scanf("%d", &T);
    for(int co = 1; co <= T; co++) {
        input();
        int ans = judge();
        if(ans != -1)   printf("Case %d: %d\n", co, ans);
        else   printf("Case %d: impossible\n", co);
    }
    return 0;
}
