#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

int n;
struct Node {
    int x, y;
    int visited[20][20];
} x;

int dfs(Node cur) {
    for (int i = 0; i < 4; i++) {
        int nx = cur.x + dx[i], ny = cur.y + dy[i];
        if (!cur.visited[nx][ny]) {
            cur.x += dx[i];  cur.y += dy[i];
            cur.visited[nx][ny] = true;
            if (dfs(cur) == 0) return 1;  // N -> P
            cur.visited[nx][ny] = false;
            cur.x -= dx[i];  cur.y -= dy[i];
        }
    }
    return 0;  // P -> N
}

int main() {
/*
    for (int i = 1; i <= 15; i++) {
        memset(x.visited, false, sizeof(x.visited));
        for (int j = 0; j <= i+1; j++) {
            x.visited[0][j] = true;
            x.visited[i+1][j] = true;
            x.visited[j][0] = true;
            x.visited[j][i+1] = true;
        }
        x.visited[1][1] = true;
        x.x = 1;  x.y = 1;

        printf("%d: %d\n", i, dfs(x));
    }
*/
    while (~scanf("%d", &n) && n) {
        if (n % 2 == 0) {
            printf("8600\n");
        } else {
            printf("ailyanlu\n");
        }
    }
    return 0;
}
