#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 362880;  // 9! = 362880
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
const int fac[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};  // C(n, m)
const char dir[] = "udlr";

bool visited[MAXN];
int pre[MAXN], q[MAXN], head, tail;
char action[MAXN];

struct Node {
    char puzzle[9];
    char xy;
} start;

int Kangtuo(const char *s) {  //康托展开
    int num = 0;
    for (int i = 0; i < 8; i++) {
        int temp = 0;
        for (int j = i + 1; j < 9; j++)
            if (s[j] < s[i])
                temp++;
        num += fac[s[i] - 1] * temp;
    }
    return num;
}

Node ReKangtuo(int num) {  //康托逆展开
    Node tmp;
    int i, a[9];
    for (i = 2; i <= 9; i++) {
        a[i - 1] = num % i;
        num = num / i;
        tmp.puzzle[i - 1] = 0;
    }
    tmp.puzzle[0] = 0;
    for (int k = 9; k >= 2; k--) {
        int t = 0;
        for (i = 8; i >= 0; i--) {
            if (tmp.puzzle[i] != 0) continue;
            if (t == a[k - 1]) break;
            t++;
        }
        tmp.puzzle[i] = k;
    }
    for (i = 0; i < 9; i++)
        if (tmp.puzzle[i] == 0) {
            tmp.puzzle[i] = 1;
            break;
        }
    tmp.xy = 8 - a[8];
    return tmp;
}

void BFS() {
    memset(visited, false, sizeof(visited));
    int u = Kangtuo(start.puzzle);
    pre[u] = -1;
    visited[u] = 1;

    head = tail = 0;
    q[tail++] = u;

    while (head < tail) {
        u = q[head];
        head++;

        Node cur = ReKangtuo(u);

        int xy = cur.xy;
        int x = xy / 3;
        int y = xy % 3;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx <= 2 && ny >= 0 && ny <= 2) {
                Node tmp = cur;
                tmp.xy = nx * 3 + ny;

                char t = tmp.puzzle[xy];
                tmp.puzzle[xy] = tmp.puzzle[tmp.xy];
                tmp.puzzle[tmp.xy] = t;

                int v = Kangtuo(tmp.puzzle);
                if (!visited[v]) {
                    action[v] = i;
                    visited[v] = true;
                    pre[v] = u;
                    if (v == 0) return;
                    q[tail++] = v;
                }
            }
        }
    }
}

void printPath() {
    int n = 1, u;
    char path[1000];
    path[0] = action[0];
    u = pre[0];
    while (pre[u] != -1) {
        path[n++] = action[u];
        u = pre[u];
    }
    for (int i = n - 1; i >= 0; i--)
        printf("%c", dir[path[i]]);
}

void solve() {
    char str[4];
    for (int i = 0; i < 9; i++) {
        scanf("%s", str);
        if (str[0] == 'x') {
            start.puzzle[i] = 9;
            start.xy = i;
        } else
            start.puzzle[i] = str[0] - '0';
    }

    BFS();

    if (visited[0]) {
        printPath();
    } else {
        printf("unsolvable\n");
    }
}

int main() {
    solve();
    return 0;
}
