#include <iostream>
#include <cstring>
#include <string>
using namespace std;

const int MAXN = 1000010;
int N, next[MAXN], nCase;
string S;

void getNext(string pattern) {
    memset(next, 0, sizeof(next));
    for (int i = 1; i < pattern.size(); i++) {
        int j = i;
        while (j > 0) {
            j = next[j];
            if (pattern[j] == pattern[i]) {
                next[i+1] = j + 1;
                break;
            }
        }
    }
}

void output() {
    cout << "Test case #" << nCase << endl;
    for (int i = 2; i <= N; i++) {
        //cout << i << " " << next[i] << endl;
        if (next[i] > 0 && i % (i - next[i]) == 0) {
            cout << i << " " << i / (i - next[i]) << endl;
        }
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> N && N) {
        nCase++;
        cin >> S;
        getNext(S);
        output();
    }
    return 0;
}
