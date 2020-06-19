#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
short f[5002][5002]{};
short a[1002]{};
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        memset(f, 0, sizeof(f));
        for (int i{1}; i <= n; i++) {
            cin >> a[i];
        }
        for (int i{1}; i <= n; i++) {
            for (int j{1}; j <= i; j++)
                f[i][j] = max(f[i - 1][j - 1], f[i - 1][j]);
            if (a[i] <= i)
                f[i][a[i]] = max(f[i][a[i]], short(f[i - 1][a[i] - 1] + 1));
        }
        short ans{};
        for (int i{n}; i >= 0; i--)
            ans = max(ans, f[n][i]);
        cout << ans << endl;
    }
}