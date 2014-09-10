#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 100010;
int N, M, nCase, father[MAXN], bang[MAXN];

int find_set(int x) {
    if (x == father[x]) return x;
    int tmp = father[x];
    father[x] = find_set(father[x]);
    bang[x] = (bang[x] + bang[tmp]) % 2;
    return father[x];
}

void union_set(int x, int y) {
    x = find_set(x);
    y = find_set(y);
    if (x == y) return;

    father[x] = y;
    bang[x] = (bang[x] + 1 + bang[y]) % 2;
}

void init() {
    for (int i = 1; i <= N; i++) {
        father[i] = i;
        bang[i] = 0;
    }
}

void solve() {
    for (int i = 0; i < M; i++) {
        char op;
        int a, b;
        //cin >> op >> a >> b;
        getchar();
        scanf("%c%d%d", &op, &a, &b);
        if (op == 'D') {
            union_set(a, b);
        } else if (op == 'A') {
            if (find_set(a) != find_set(b)) {
                //cout << "Not sure yet." << endl;
                printf("Not sure yet.\n");
            } else {
                if (bang[a] != bang[b]) {
                    //cout << "In different gangs." << endl;
                    printf("In different gangs.\n");
                } else {
                    //cout << "In the same gang." << endl;
                    printf("In the same gang.\n");
                }
            }
        }
    }
}

int main() {
    //cin >> nCase;
    scanf("%d", &nCase);
    while (nCase--) {
        //cin >> N >> M;
        scanf("%d%d", &N, &M);
        init();
        solve();
    }
    return 0;
}
