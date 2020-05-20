#include <cstring>
#include <iostream>
using namespace std;

int a[10005] = {};

/**
 * f: DP (same as example 'magical pocket')
 * [use first i coins][the price of goods]
 * Returns: how many solutions
 * 
 * Formula:
 * f[i][j] = (
 *     j < a[i]?
 *         f[i - 1][j]                      // can't take this coin
 *     :
 *         f[i - 1][j] + f[i - 1][j - a[i]] // take or not take this coin
 *     )
 * ;
 * 
 * While using 'rolling array' to save memory.
 * Adjust the looping sequence, and just use
 * f[j] = f[j] + f[j - a[i]], for j from x to a[i] (steps -1), for i from 1 to n
 */
int f[10005] = {};

/**
 * g: DP
 * [a certain coin number i][the price of goods]
 * Returns: without coin number i, how many solutions
 * 
 * Formula:
 * g[i][j] = (
 *     j >= a[i] ?
 *         f[j] - g[i][j - a[i]]
 *     :
 *         f[j]
 *     )
 * ; 
 * // That's because, when we saying f[i], it contains two part:
 * // 1. Solutions using coin i;
 * // 2. Solutions without coin i, which is we want to know.
 * // Now try to calculate how many solution in part 1. 
 * // If j < a[i], then part 1 is an empty set, which means g[j] = f[j].
 * // Otherwise, throw the coin i from those solutions.
 * // And the problem turns into:
 * // Without coin i, how many solutions to reach the prize (j - a[i]).
 * // That's the result of g[i][j - a[i]].
 * 
 * Mentioned that i is not used in formula, so deprecate it. Like:
 * g[j] = (j >= a[i] ? f[j] - g[j - a[i]] : f[j]) 
 * , for j from 1 to a[i]
 * , for i from 1 to n
 */
int g[10005] = {};
int res[10005] = {};
int num = 0;
int main() {
    int n, x;
    cin >> n >> x;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = x; j >= a[i]; j--) {
            f[j] += f[j - a[i]];
        }
    }
    for (int i = 1; i <= n; ++i) {
        memset(g, 0, sizeof(g));
        for (int j = 0; j <= x; ++j) {
            if (j >= a[i])
                g[j] = f[j] - g[j - a[i]];
            else
                g[j] = f[j];
        }
        if (g[x] == 0)
            res[num++] = a[i];
    }
    cout << num << endl;
    for (int i = 0; i < num; ++i)
        cout << res[i] << ' ';
}