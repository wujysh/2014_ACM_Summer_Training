#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 13;
const int mod = 10000007;
int n, nn, mm;

struct Mat {
    long long mat[MAXN][MAXN];
} inputMat, baseMat;

Mat operator *(Mat a, Mat b) {
    Mat c;
    memset(c.mat, 0, sizeof(c.mat));
    for (int k = 0 ; k < n ; k++) {
        for (int i = 0 ; i < n ; i++) {
            if (a.mat[i][k] == 0) continue; //优化
            for (int j = 0 ; j < n ; j++) {
                if (b.mat[k][j] == 0) continue; //优化
                c.mat[i][j] = (c.mat[i][j] + (a.mat[i][k] * b.mat[k][j]) % mod) % mod;
            }
        }
    }
    return c;
}

Mat operator ^(Mat a, int k) {
    Mat c;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c.mat[i][j] = (i == j);
    for (; k ; k >>= 1) {
        if (k & 1) c = c * a;
        a = a * a;
    }
    return c;
}

void init() {
    memset(baseMat.mat, 0, sizeof(baseMat.mat));
    for (int i = 0; i < nn; i++) {
        for (int j = i; j < nn; j++) {
            baseMat.mat[i][j] = 1;
        }
    }
    for (int j = 0; j < nn; j++) {
        baseMat.mat[nn][j] = 10;
        baseMat.mat[nn+1][j] = 1;
    }
    baseMat.mat[nn][nn] = 10;
    baseMat.mat[nn+1][nn] = 1;
    baseMat.mat[nn+1][nn+1] = 1;
}

void input() {
    n = nn + 3;
    for (int i = 0; i < nn; i++) {
        scanf("%I64d", &inputMat.mat[0][i]);
    }
    inputMat.mat[0][nn] = 23;
    inputMat.mat[0][nn+1] = 3;
}

void output(Mat m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << m.mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void solve() {
    Mat newMat = baseMat ^ mm;
    Mat ansMat = inputMat * newMat;
    printf("%I64d\n", ansMat.mat[0][nn-1]);
}

int main() {
    while (~scanf("%d%d", &nn, &mm)) {
        init();
        input();
        solve();
    }
    return 0;
}
