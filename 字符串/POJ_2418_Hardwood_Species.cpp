#include <iostream>
#include <iomanip>
#include <string>
#include <map>
using namespace std;

map<string, int> tree;
string name;
int cnt;

int main() {
    ios::sync_with_stdio(false);

    while (getline(cin, name)) {
        tree[name]++;
        cnt++;
    }

    map<string, int>::iterator it;
    for (it = tree.begin(); it != tree.end(); it++) {
        cout << it->first << " " << fixed << setprecision(4) << (it->second * 100.0 / cnt) << endl;
    }

    return 0;
}
