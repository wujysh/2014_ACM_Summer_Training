#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 10010;
int n, father[MAXN], a, b, t, nCase;
vector<int> fa, fb;

void init() {
    memset(father, -1, sizeof(father));
    fa.clear();
    fb.clear();
}

void input() {
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int x, y;
        cin >> x >> y;
        father[y] = x;
    }
    cin >> a >> b;
}

void work() {
    t = a;
    while (t != -1) {
        fa.push_back(t);
        t = father[t];
    }
    t = b;
    while (t != -1) {
        fb.push_back(t);
        t = father[t];
    }

    sort(fa.begin(), fa.end());
    for (int i = 0; i < fb.size(); i++) {
        if (binary_search(fa.begin(), fa.end(), fb[i])) {
            cout << fb[i] << endl;
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    while (nCase--) {
        init();
        input();
        work();
    }
    return 0;
}
