#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>
using namespace std;

const int MAXN = 110;
int n;
string line[MAXN];

struct Node {
    char ch;
    int cnt;
    bool operator<(const Node &b) const {
        if (cnt == b.cnt) {
            return ch < b.ch;
        } else {
            return cnt > b.cnt;
        }
    }
};
vector<Node> nodes;

void init() {
    nodes.clear();
    nodes.resize(26);
    for (int i = 0; i < 26; i++) {
        nodes[i].ch = char('A' + i);
    }
}

void input() {
    cin.ignore();
    for (int i = 0; i < n; i++) {
        getline(cin, line[i]);
    }
}

void work() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < line[i].length(); j++) {
            if (isalpha(line[i][j])) {
                nodes[toupper(line[i][j]) - 'A'].cnt++;
            }
        }
    }
    sort(nodes.begin(), nodes.end());
}

void output() {
    for (int i = 0; i < 26; i++) {
        if (nodes[i].cnt == 0) break;
        cout << nodes[i].ch << " " << nodes[i].cnt << endl;
    }
}

int main() {
    while (cin >> n) {
        init();
        input();
        work();
        output();
    }
    return 0;
}
