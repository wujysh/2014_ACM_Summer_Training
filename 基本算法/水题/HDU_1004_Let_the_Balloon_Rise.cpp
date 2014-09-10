#include <iostream>
#include <map>
using namespace std;

map<string, int> cnt;
int ans, n;
string ans_color;

void init() {
    cnt.clear();
    ans = 0;
}

void input() {
    for (int i = 0; i < n; i++) {
        string color;
        cin >> color;
        int tmp = 0;
        if (cnt.find(color) != cnt.end()) {
            tmp = ++cnt[color];
        } else {
            tmp = cnt[color] = 1;
        }
        if (tmp > ans) {
            ans = tmp;
            ans_color = color;
        }
    }
}

void output() {
    cout << ans_color << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n && n) {
        init();
        input();
        output();
    }
    return 0;
}
