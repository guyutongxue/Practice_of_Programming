#include <cstdint>
#include <iostream>
using namespace std;

/**
 * s: requisite
 * [i: position][j: position]
 * Returns: number formed from pos i to pos j
 *
 */
int64_t s[50][50] = {};

/**
 * f: DP
 * [t: number of operator*][i: how many numbers]
 * Returns: The maximum product of inserting t operator* into first i number
 *
 * Formula:
 * f[t][i] = max [
 *     f[t - 1][j] + s[j + 1][i],
 *     for j from 1 to i - 1
 * ];
 *
 */
int64_t f[50][50];

int main() {
    int n, k;
    cin >> n >> k;
    char str[1000];
    cin >> str;
    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; ++j)
            s[i][j] = s[i][j - 1] * 10 + str[j - 1] - '0';
    for (int i = 1; i <= n; ++i)
        f[0][i] = s[1][i];
    for (int t = 1; t <= k; ++t) {
        for (int i = t + 1; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                f[t][i] = max(f[t][i], f[t - 1][j] * s[j + 1][i]);
            }
        }
    }
    cout << f[k][n] << endl;
    return 0;
}