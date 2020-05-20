
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
using lint = long long;

/**
 * f: DP
 * [sum of the sequence][last element of sequence]
 * Returns: how many increasing secuence with such requirements
 *
 * Formula:
 * f[i][j] =
 *     (i == j ?
 *         1                  // Only 1 element in the sequence in this situation
 *     :
 *         sum [
 *             f[i - j][k]    // Without j, last element is other number lower than j
 *             , for k from 1 to j
 *         ]
 *     )
 * ;
 */
lint f[252][252] = {};

/**
 * g: DP
 * [sum of the sequence][the value of 'middle']
 * Returns: how many UPDs with such requirements
 *
 * Formula: // see below
 */
lint g[252][252] = {};

/**
 * result:
 * [sum of the sequence]
 * Returns: how many UDPs.
 *
 * Formula:
 * result[i] = sum [
 *     g[i][j]
 *     , for j from 1 to i
 * ];
 */
lint result[252] = {};

int main() {
    for (int i = 1; i < 252; i++) {
        for (int j = 1; j <= i; j++) {
            if (i == j)
                f[i][j] = 1;
            else
                for (int k = 1; k <= j; k++) {
                    f[i][j] += f[i - j][k];
                }
        }
    }
    for (int i = 1; i < 252; i++) {
        for (int j = 1; j <= i; j++) {
            if (i == j)
                g[i][j] = 1;                              // if only have one element : j
            else {                                        // or...
                int temp = i - j;                         // sum without middle one
                if (temp % 2 == 0)                        // can divide into 2 part
                    g[i][j] += f[temp / 2 + j][j];        // just add num of one side: _ _ _ j _ _ _
                if (temp > j && (temp - j) % 2 == 0)      // if we could pick another j out...
                    g[i][j] += f[(temp - j) / 2 + j][j];  // then calculate num as: _ _ _ j j _ _ _
                else if (temp == j)                       // if after picking j, nothing left
                    g[i][j]++;                            // just add 1: j j
            }
            result[i] += g[i][j];
        }
    }
    int n;
    while (cin >> n, n) {
        cout << n << ' ' << result[n] << endl;
    }
    return 0;
}