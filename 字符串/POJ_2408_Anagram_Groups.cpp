#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
using namespace std;

const int MAXN = 30010;
string str;
map<string, int> m;
vector<string> group[MAXN];
int cnt;

bool cmp(vector<string> a, vector<string> b) {
    if (a.size() == b.size() && !a.empty() && !b.empty()) {
        return a[0] < b[0];
    }
    return a.size() > b.size();
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> str) {
        string tmp = str;
        sort(tmp.begin(), tmp.end());
        if (m.find(tmp) != m.end()) {
            group[m[tmp]].push_back(str);
        } else {
            m[tmp] = cnt;
            group[cnt++].push_back(str);
        }
    }

    sort(group, group+cnt, cmp);
    for (int i = 0; i < 5; i++) {
        sort(group[i].begin(), group[i].end());
        cout << "Group of size " << group[i].size() << ": ";
        group[i].erase(unique(group[i].begin(), group[i].end()), group[i].end());
        for (int j = 0; j < group[i].size(); j++) {
            cout << group[i][j] << " ";
        }
        cout << "." << endl;
    }
    return 0;
}
