#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

set<string> mem[6];
int n;
vector<string> vs;

void init() {
    for (int i = 0; i <= 5; i++) {
        mem[i].clear();
    }
    mem[1].insert("joe");
    vs.clear();
}

bool isEnd(string tmp) {
    return tmp == "." || tmp == "," || tmp == ":" || tmp == "?" || tmp == "!";
}

void learnSentence(vector<string> words) {
    for (int i = 0 ; i  < words.size(); i++) {
        transform(words[i].begin(), words[i].end(), words[i].begin(), ::tolower);
    }
    for (int i = 0; i < words.size(); i++) {
        string temp = words[i] ;
        if (mem[1].find(temp) == mem[1].end()) {
            mem[1].insert(temp);
        }
        for (int len = 2; len <= n && i + len - 1 < words.size(); len++) {
            temp = temp + '#' + words[i + len - 1];
            if (mem[len] .find(temp) == mem[len] .end()) {
                mem[len] .insert(temp);
            }
        }
    }
}

void judge(vector<string> ss) {
    int len = ss.size();
    for (int i = 0 ; i  < len; i++) {
        transform(ss[i].begin(), ss[i].end(), ss[i].begin(), ::tolower);
    }
    bool flag = false;
    string tst;
    tst += vs[0];
    for (int i = 1; i < len; i++) {
        tst += " ";
        tst += vs[i];
    }
    for (int i = 0; i < len; i++) {
        if (mem[1].find(ss[i]) == mem[1].end()) {
            mem[1].insert(ss[i]);
            printf("What does the word \"%s\" mean?\n", vs[i].c_str());
            flag = 1;
        }
    }
    if (flag) {
        if (len > 1) printf("What does the sentence \"%s\" mean?\n", tst.c_str());
        learnSentence(ss);
        return;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < len - i + 1; j++) {
            string tmp;
            tmp.clear();
            tmp += ss[j];
            for (int k = 1; k < i; k++) {
                tmp += "#";
                tmp += ss[j + k];
            }
            if (mem[i].find(tmp) == mem[i].end()) {
                flag = true;
                break;
            }
        }
    }
    if (flag)  {
        learnSentence(ss);
        if (len > 1) printf("What does the sentence \"%s\" mean?\n", tst.c_str());
    }
}

int main() {
    int T = 1;
    while (~scanf("%d", &n)) {
        init();
        if (T != 1) puts("");
        string str;
        while (cin >> str) {
            if (isEnd(str)) {
                learnSentence(vs);
                vs.clear();
            } else if (str == "*") {
                if (vs.size() != 0) learnSentence(vs);
                vs.clear();
                break;
            } else {
                vs.push_back(str);
            }
        }
        printf("Learning case %d\n", T++);
        while (cin >> str) {
            if (isEnd(str)) {
                judge(vs);
                vs.clear();
            } else if(str == "#") {
                if (vs.size() != 0) judge(vs);
                vs.clear();
                break;
            } else {
                vs.push_back(str);
            }
        }
    }
    return 0;
}
