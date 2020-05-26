// ybt 1195

#include <iostream>
using namespace std;

/**
 * f: DP
 * [i: first i number][j: mod result]
 * Returns: Is first i number exists a combination which mod k equals j?
 *
 * Formula:
 * f[i][j] =
 *     f[i - 1][(k + j - a[i] % k) % k] ||  // If take negative operatoer here
 *                                          // (add a k prevent negative result)
 *     f[i - 1][(j + a[i] % k) % k]         // Else take positive operator here
 * ;
 */
bool f[10002][102];

// data
int a[10002];

int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    f[0][0] = true;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k - 1; j++) {
            f[i][j] = f[i - 1][(k + j - a[i] % k) % k] || f[i - 1][(j + a[i] % k) % k];
        }
    }
    cout << (f[n][0] ? "YES" : "NO") << endl;
}