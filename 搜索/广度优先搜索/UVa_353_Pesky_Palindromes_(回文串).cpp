#include <iostream>
#include <string>
#include <cstdio>
#include <queue>
#include <set>
using namespace std;

set<string> word;
string line;

struct Node {
    int pos, len;
    Node() {}
    Node(int _pos, int _len) : pos(_pos), len(_len) {}
};
queue<Node> q;

void init() {
    word.clear();
}

void solve() {
    for (int i = 0; i < line.size(); i++) {
        word.insert(line.substr(i, 1));
        q.push(Node(i, 1));
    }
    for (int i = 0; i < line.size()-1; i++) {
        if (line[i] == line[i+1]) {
            word.insert(line.substr(i, 2));
            q.push(Node(i, 2));
        }
    }

    while (!q.empty()) {
        Node cur = q.front();
        q.pop();

        int len = cur.len;
        if (cur.pos-1 >= 0 && cur.pos+cur.len < line.size() && line[cur.pos-1] == line[cur.pos+cur.len]) {
            word.insert(line.substr(cur.pos-1, cur.len+2));
            q.push(Node(cur.pos-1, cur.len+2));
        }
    }

    cout << "The string '" << line << "' contains " << word.size() << " palindromes." << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (getline(cin, line)) {
        init();
        solve();
    }
    return 0;
}
