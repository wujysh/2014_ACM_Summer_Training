#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
#include <map>
using namespace std;

const int MAXN = 7;
map<string, int> cnt[MAXN], combine;
string str;
int day;
struct Word {
    string word;
    int cnt;
    Word() {}
    Word(string _word, int _cnt) : word(_word), cnt(_cnt) {}
    bool operator < (const Word &b) const {
        if (cnt == b.cnt) return word < b.word;
        return cnt > b.cnt;
    }
};
vector<Word> result;

int main() {
    //freopen("test.in", "r", stdin);
    //freopen("text.out", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin >> str) {
        if (str == "<text>") {
            cnt[day].clear();

            while (cin >> str && str != "</text>") {
                if (str.length() < 4) continue;
                cnt[day][str]++;
            }
            day = (day + 1) % MAXN;
        } else if (str == "<top") {
            combine.clear();
            result.clear();

            int top;
            cin >> top >> str;

            map<string, int>::iterator it;
            for (int i = 0; i < MAXN; i++) {
                for (it = cnt[i].begin(); it != cnt[i].end(); it++) {
                    combine[it->first] += it->second;
                }
            }
            for (it = combine.begin(); it != combine.end(); it++) {
                result.push_back(Word(it->first, it->second));
            }

            cout << "<top " << top << ">" << endl;
            sort(result.begin(), result.end());
            int i;
            for (i = 0; i < min(top, (int)result.size()); i++) {
                cout << result[i].word << " " << result[i].cnt << endl;
            }
            while (i < result.size() && result[i].cnt == result[i-1].cnt) {
                cout << result[i].word << " " << result[i].cnt << endl;
                i++;
            }
            cout << "</top>" << endl;
        }
    }
    return 0;
}
