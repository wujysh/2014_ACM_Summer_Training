#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

const int MAXN = 400010;
int Next[MAXN];
string str;
char line[400010];

void getNext(string pattern) {
    memset(Next, 0, sizeof(Next));
    for (int i = 1; i < pattern.length(); i++) {
        int j = i;
        while (j > 0) {
            j = Next[j];
            if (pattern[j] == pattern[i]) {
                Next[i+1] = j + 1;
                break;
            }
        }
    }
}

void solve() {
    str = line;
    getNext(str);
    vector<int> ans;
    int t = str.length();
    while (t > 0) {
        ans.push_back(t);
        t = Next[t];
    }
    for (int i = ans.size()-1; i >= 0; i--) {
        printf("%d", ans[i]);
        if (i > 0) printf(" ");
    }
    printf("\n");
}

int main() {
    while (~scanf("%s", line)) {
        solve();
    }
    return 0;
}
