#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

/**
 * f: DP
 * [i: number of floors][j: number of eggs]
 * Returns: throw times in the worst condition
 * f[i][j] = minimum of [
 *     for int k from 1 to i: // throw an egg from floor k
 *     min(
 *         f[k - 1][j - 1], // if it break on floor k, so try k-1 next time
 *         f[i - k][j]      // if not break, try floors betwwen k from i (same as i-k)
 *     ) + 1;               // throwing times ++
 * ]
 */
int f[102][12];
int main() {
    int n, m;
    while (cin >> n >> m) {
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                f[i][j] = i;
            }
        }
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= j; k++) {
                for (int i = 2; i <= m; i++) {
                    f[j][i] = min(f[j][i], max(f[k - 1][i - 1], f[j - k][i]) + 1);
                }
            }
        }
        cout << f[n][m] << endl;
    }
    return 0;
}