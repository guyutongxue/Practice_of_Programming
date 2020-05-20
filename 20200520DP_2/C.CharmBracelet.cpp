#include <algorithm>
#include <cstdio>
using namespace std;
/**
 * f: DP (same as example '0-1 pack problem')
 * [taking first i charms][the maximum weight]
 * Returns: how many solutions
 *
 * Formula:
 * f[i][j] = (
 *     j < a[i]?
 *         f[i - 1][j]                    // can't take this charm
 *     :
 *         max (
 *              f[i - 1][j],              // take this charm, or
 *              f[i - 1][j - w[i]] + v[i] // don't take this charm
 *         )
 *     )
 * ;
 *
 * While using 'rolling array' to save memory.
 * Adjust the looping sequence, and use
 * f[j] = max(f[j], f[j - w[i]] + v[i])
 * ,for j from m to w[i] (steps -1), for i from 1 to n
 */
int f[13000] = {};

// weights
int w[3500] = {};
// values
int v[3500] = {};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= m; i++) {
        f[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &w[i], &v[i]);
    }
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= w[i]; j--) {
            f[j] = max(f[j], f[j - w[i]] + v[i]);
        }
    printf("%d\n", f[m]);
    return 0;
}