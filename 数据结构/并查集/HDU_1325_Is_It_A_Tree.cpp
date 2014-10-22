#include <iostream>
#include <cstdio>
#include <set>
using namespace std;

const int MAXN = 1010;
int a, b, cnt, father[MAXN], rank_set[MAXN], merge_cnt, in_degree[MAXN];
bool flag;
set<int> node_cnt;

int find_set(int x) {
    return father[x] == x ? x : father[x] = find_set(father[x]);
}

void union_set(int x, int y) {
    int a = find_set(x), b = find_set(y);
    if (a == b) return;
    merge_cnt++;
    if (rank_set[a] < rank_set[b]) {
        father[a] = b;
    } else {
        father[b] = a;
        if (rank_set[a] == rank_set[b]) {
            rank_set[a]++;
        }
    }
}

void init() {
    for (int i = 1; i < MAXN; i++) {
        father[i] = i;
        rank_set[i] = 1;
        in_degree[i] = 0;
    }
    flag = true;
    node_cnt.clear();
    merge_cnt = 0;
}

void solve() {
    if (a == 0 && b == 0) {
        if (flag && merge_cnt == node_cnt.size() - 1) {
            printf("Case %d is a tree.\n", ++cnt);
        } else {
            printf("Case %d is not a tree.\n", ++cnt);
        }
        init();
    } else if (flag) {
        node_cnt.insert(a);
        node_cnt.insert(b);
        in_degree[b]++;
        if (in_degree[b] > 1 || find_set(a) == find_set(b)) {
            flag = false;
        } else {
            union_set(a, b);
        }
    }
}

int main() {
    init();
    while (~scanf("%d%d", &a, &b)) {
        if (a == -1 && b == -1) {
            break;
        }
        solve();
    }
    return 0;
}
