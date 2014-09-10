#include <iostream>
#include <cstring>
#include <string>
using namespace std;

const int MAXM = 10010;
const int MAXN = 1000010;
int text[MAXN], pattern[MAXM], T, N, M, next[MAXN], ans;

void getNext() {
    for (int i = 1; i < M; i++) {
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

int findSubstr() {
    for (int i = 0, j = 0; i < N; i++) {
        if (j < M && text[i] == pattern[j]) {
            j++;
        } else {
            while (j > 0) {
                j = next[j];
                if (text[i] == pattern[j]) {
                    j++;
                    break;
                }
            }
        }
        if (j == M) {
            return i - M + 2;
        }
    }
    return -1;
}

void input() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> text[i];
    }
    for (int i = 0; i < M; i++) {
        cin >> pattern[i];
    }
}

void work() {
    getNext();
    ans = findSubstr();
}

void output() {
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        input();
        work();
        output();
    }
    return 0;
}
