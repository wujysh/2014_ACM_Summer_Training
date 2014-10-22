#include <iostream>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
#include <stack>
using namespace std;

struct Node {
    char ch;
    int cnt;
    Node() {}
    Node(char _ch, int _cnt) : ch(_ch), cnt(_cnt) {}
    bool operator < (const Node &b) const {
        return ch < b.ch;
    }
};
stack<Node> st;
vector<Node> ans;
int cnt, nCase;
string line;

void solve() {
    getline(cin, line);
    while (!st.empty()) {
        st.pop();
    }
    ans.clear();
    st.push(Node(line[0], 0));
    for (int i = 1; i < line.size(); i++) {
        Node top = st.top();
        if (top.ch == line[i]) {
            st.pop();
            ans.push_back(top);
            if (!st.empty()) {
                st.top().cnt++;
            }
        } else {
            st.push(Node(line[i], 1));
        }
    }

    sort(ans.begin(), ans.end());
    cout << "Case " << ++cnt << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i].ch << " = " << ans[i].cnt << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> nCase;
    getline(cin, line);
    while (nCase--) {
        solve();
    }
    return 0;
}
