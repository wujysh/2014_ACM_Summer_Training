#include <iostream>
#include <cstdio>
#include <string>
#include <map>
using namespace std;

const int MAXN = 10010;
const int ROOT = 0;
map<string, int> mp[MAXN];
int T, Q, curPos, mpCnt;
string text;

int parse(int cnt, int deep) {
    mp[cnt].clear();

    if (text[curPos] == '{') {  // multiple
        while (text[curPos++] != '}') {
            if (text[curPos] == '"') {
                int startPos = curPos, len = 1;
                while (text[++curPos] != '"') len++;
                string key = text.substr(startPos, len + 1);
                if (text[++curPos] == ':') {
                    curPos++;
                    mp[cnt][key] = parse(++mpCnt, deep + 1);
                }
            }
        }
    } else {  // single
        if (text[curPos] == '"') {
            int startPos = curPos, len = 1;
            while (text[++curPos] != '"') len++;
            string value = text.substr(startPos, len + 1);
            mp[cnt][value] = -1;
        }
    }
    return cnt;
}

void print(int father) {
    if (mp[father].size() == 1 && mp[father].begin()->second == -1) {
        cout << mp[father].begin()->first;
        return;
    }
    cout << '{';
    map<string, int>::iterator it;
    for (it = mp[father].begin(); it != mp[father].end(); it++) {
        cout << it->first << ':';
        print(it->second);
        if (it != --mp[father].end()) cout << ',';
    }
    cout << '}';
}

void init() {
    getline(cin, text);
    mpCnt = curPos = 0;
    parse(0, 1);
}

void solve() {
    cin >> Q;
    getline(cin, text);
    while (Q--) {
        bool flag = true;
        int curMp = ROOT;

        getline(cin, text);
        curPos = -1;
        while (++curPos < text.size()) {
            int startPos = curPos, len = 1;
            while (curPos < text.size() && text[++curPos] != '.') len++;
            string key = text.substr(startPos, len);
            if (mp[curMp].find(key) != mp[curMp].end()) {
                curMp = mp[curMp][key];
            } else {
                flag = false;
                break;
            }
        }
        if (flag) {
            print(curMp);
            cout << endl;
        } else {
            cout << "Error!" << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    getline(cin, text);
    while (T--) {
        init();
        solve();
    }
    return 0;
}
