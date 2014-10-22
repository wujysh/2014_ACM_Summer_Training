#include <iostream>
#include <string>
using namespace std;

string line;

int main() {
    ios::sync_with_stdio(false);
    while (getline(cin, line)) {
        int len = line.size();
        for (int i = 0; i < len; i++) {
            if (len - i >= 5 && line.substr(i, 5) == "Apple") {
                cout << "MAI MAI MAI!" << endl;
                continue;
            }
            if (len - i >= 6 && line.substr(i, 6) == "iPhone") {
                cout << "MAI MAI MAI!" << endl;
                continue;
            }
            if (len - i >= 4 && line.substr(i, 4) == "iPod") {
                cout << "MAI MAI MAI!" << endl;
                continue;
            }
            if (len - i >= 4 && line.substr(i, 4) == "iPad") {
                cout << "MAI MAI MAI!" << endl;
                continue;
            }
            if (len - i >= 4 && line.substr(i, 4) == "Sony") {
                cout << "SONY DAFA IS GOOD!" << endl;
                continue;
            }
        }
    }
    return 0;
}
