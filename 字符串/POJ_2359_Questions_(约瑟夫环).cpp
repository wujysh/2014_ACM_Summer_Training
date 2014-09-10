#include <iostream>
#include <string>
using namespace std;

const int N = 1999;
string line, str;

int main() {
    ios::sync_with_stdio(false);
    while (getline(cin, line)) {
        str += line;
    }
    int i = 0;
    while (str.length() > 1) {
        i = (i-1 + N) % str.length();
        str.erase(str.begin() + i);
    }
    if (str[0] == '?') {
        cout << "Yes" << endl;
    } else if (str[0] == ' ') {
        cout << "No" << endl;
    } else {
        cout << "No comments" << endl;
    }
    return 0;
}
