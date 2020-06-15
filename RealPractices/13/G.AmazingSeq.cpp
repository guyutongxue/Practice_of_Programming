#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int f[202][202]{};
int a[202]{};
int main() {
    int t;
    cin >> t;
    for (int cases{1}; cases <= t; cases++) {
        memset(f, 0x7f, sizeof(f));
        int n;
        cin >> n;
        for (int i{0}; i < n; i++) {
            cin >> a[i];
            f[i][i] = 1;
        }
        for (int i{0}; i < n; i++) {
            for (int j{0}; j < i; j++) {
                f[i][j] = 0;
            }
        }
        for (int i{0}; i < n - 1; i++) {
            f[i][i + 1] = (a[i] == a[i + 1] ? 1 : 2);
        }
        for (int i{n - 2}; i >= 0; i--) {
            for (int j{i + 1}; j < n; j++) {
                for (int k{i}; k < j; k++) {
                    if (a[k] == a[j]) {
                        f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j - 1]);
                    }
                    f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
                }
            }
        }
        cout << "Case " << cases << ": " << f[0][n - 1] << endl;
    }
}