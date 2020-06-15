// Same as Practice/10/H, ybt 1302

#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

int a[100005]{};
long long f[2][100005]{};
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i{1}; i <= n; i++) {
            cin >> a[i];
        }
        memset(f, 0, sizeof(f));
        for (int i{1}; i <= n; i++) {
            f[1][i] = f[0][i - 1] + a[i];
            f[0][i] = max(f[0][i - 1], f[1][i - 1]);
        }
        cout << max(f[0][n], f[1][n]) << endl;
    }
}