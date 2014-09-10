#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <map>
using namespace std;

const int MAXN = 30010;
int n, q, last[MAXN], deep[MAXN], father[MAXN], cnt;
string name[MAXN];
vector<int> son[MAXN];
map<string, int> nameId;

void init() {
    for (int i = 0; i < MAXN; i++) {
        son[i].clear();
    }
    cnt = 1;
    nameId.clear();
}

void input() {
    string line;
    cin >> line;
    name[cnt] = line;
    last[0] = 1;
    deep[cnt] = 0;
    nameId[line] = cnt;
    father[cnt] = 0;
    cnt++;
    for (int i = 0; i < n - 1; i++) {
        cin >> line;
        int pos = line.find_last_of('.');
        name[cnt] = line.substr(pos + 1);
        deep[cnt] = pos + 1;
        son[last[pos]].push_back(cnt);
        father[cnt] = last[pos];
        last[pos + 1] = cnt;
        nameId[name[cnt]] = cnt;
        cnt++;
    }
}

bool cmp(int a, int b) {
    return name[a] < name[b];
}

void sortFamilyList(int x, int step) {
    for (int i = 0; i < step; i++) {
        putchar('.');
    }
    printf("%s\n", name[x].c_str());
    sort(son[x].begin(), son[x].end(), cmp);
    for (int i = 0; i < son[x].size(); i++) {
        int s = son[x][i];
        sortFamilyList(s, step + 1);
    }
}

int p[MAXN][20];

void init_LCA() {
    memset(p, 0, sizeof p);
    for(int i = 1; i < cnt; i++) p[i][0] = father[i];
    for(int i = 1; i < 20; i++) {
        for(int j = 1; j < cnt; j++) {
            p[j][i] = p[p[j][i - 1]][i - 1];
        }
    }
}

int LCA(int x, int y) {
    if(deep[x] > deep[y]) swap(x, y);
    int h;
    for(h = 0; 1 << h <= deep[y]; h++);
    for(int i = h - 1; i >= 0; i--) {
        if(deep[y] - (1 << i) >= deep[x]) y = p[y][i];
    }
    if(x == y) return father[x];
    for(int i = h - 1; i >= 0; i--) {
        if(p[x][i] != p[y][i]) {
            x = p[x][i], y = p[y][i];
        }
    }
    return father[x];
}

void solve() {
    string op, name1, name2;
    scanf("%d", &q);
    while (q--) {
        cin >> op;
        if (op[0] == 'L') {
            sortFamilyList(1, 0);
        } else if (op[0] == 'b') {
            cin >> name1;
            int ID = nameId[name1];
            if(ID == 1) printf("1\n");
            else printf("%d\n", son[father[nameId[name1]]].size());
        } else if (op[0] == 'c') {
            cin >> name1 >> name2;
            int x = nameId[name1], y = nameId[name2];
            printf("%s\n", name[LCA(x, y)].c_str());
        }
    }
}

int main() {
    while (~scanf("%d", &n) && n) {
        init();
        input();
        init_LCA();
        solve();
    }
    return 0;
}
