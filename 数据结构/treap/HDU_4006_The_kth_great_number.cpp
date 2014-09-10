//#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

const int MAXN = 2000010;
const int INF = 0x3f3f3f3f;
int n, k;

struct Treap {
    int root, treapCnt, key[MAXN], priority[MAXN], childs[MAXN][2], cnt[MAXN], size[MAXN];

    Treap() {
        root = 0;
        treapCnt = 1;
        priority[0] = INF;
        size[0] = 0;
    }

    void init() {
        root = 0;
        treapCnt = 1;
        priority[0] = INF;
        size[0] = 0;
    }

    void update(int x) {
        size[x] = size[childs[x][0]] + cnt[x] + size[childs[x][1]];
    }

    void rotate(int &x, int t) {
        int y = childs[x][t];
        childs[x][t] = childs[y][1-t];
        childs[y][1-t] = x;
        update(x);
        update(y);
        x = y;
    }

    void __insert(int &x, int k) {
        if (x) {
            if (key[x] == k) {
                cnt[x]++;
            } else {
                int t = key[x] < k;
                __insert(childs[x][t], k);
                if (priority[childs[x][t]] < priority[x]) {
                    rotate(x, t);
                }
            }
        } else {
            x = treapCnt++;
            key[x] = k;
            cnt[x] = 1;
            priority[x] = rand();
            childs[x][0] = childs[x][1] = 0;
        }
        update(x);
    }

    int __getKth(int &x, int k) {
        if (k <= size[childs[x][0]]) {
            return __getKth(childs[x][0], k);
        }
        k -= size[childs[x][0]] + cnt[x];
        if (k <= 0) {
            return key[x];
        }
        return __getKth(childs[x][1], k);
    }

    void insert(int k) {
        __insert(root, k);
    }

    int getKth(int k) {
        return __getKth(root, k);
    }
} treap;

void solve() {
    treap.init();
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        char op;
        //cin >> op;
        getchar();
        scanf("%c", &op);
        if (op == 'I') {
            int x;
            //cin >> x;
            scanf("%d", &x);
            treap.insert(x);
            cnt++;
        } else if (op == 'Q') {
            //cout << treap.getKth(cnt-k+1) << endl;
            printf("%d\n", treap.getKth(cnt-k+1));
        }
    }
}

int main() {
    //ios::sync_with_stdio(false);
    //while (cin >> n >> k) {
    while (~scanf("%d%d", &n, &k)) {
        solve();
    }
    return 0;
}
