#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

/**
 * h, c, p: data
 * h[i]: how happy I am
 * c[i]: cost
 * t[i]: time needed
 *
 */
int h[101]{}, c[101]{}, t[101]{};

/**
 * limited: data
 * [i: no. of activity]
 * Returns: Is activity i limited.
 *
 */
bool limited[101]{};

/**
 * f: DP
 * - Condition 1. Limited, same to 0-1 pack problem
 * [i: first i activities][j: total time][k: total money]
 * Returns: The maximum happy under the condition.
 * Formula:
 * f[i][j][k] =
 *     j - t[i] >= 0 && k - c[i] >= 0 ?
 *         f[i - 1][j][k]                              // cannot add a new activity
 *    :
 *         max (
 *             f[i - 1][j][k],                         // do not select this one
 *             f[i - 1][j - t[i]][k - c[i]] + h[i]     // select this one
 *         )
 * ;
 *
 * Notice that i can be omitted with "rolling-array". So remove that dimension,
 * while keep the loop sequence as
 * for j from MAX_TIME to 0,
 * for k from MAX_MONEY to 0.
 *
 * - Condition 2. Unlimited
 * [j: total time][k: total money]
 * Returns: the maximum happy with above condition. This time any activity is acceptable.
 * Formula:
 * f[j][k] =
 *     j - t[i] >= 0 && k - c[i] >= 0 ?
 *         f[j][k]                              // cannot add this activity
 *    :
 *         max (
 *             f[j][k],                         // do not select this one
 *             f[j - t[i]][k - c[i]] + h[i]     // select this one
 *         )
 * ;
 * for i from 1 to n,           // try for each activities
 * for j from 0 to MAX_TIME,    // in this sequence, an activity can be added more then once
 * for k from 0 to MAX_MONEY
 */
int f[2402][1002]{};

int main() {
    int days, n, money;
    cin >> days >> n >> money;
    for (int i{1}; i <= n; i++) {
        char str[15]{};
        cin >> h[i] >> c[i] >> t[i] >> str;
        if (str[0] == 'l')
            limited[i] = true;
    }
    int ans{};
    for (int d{1}; d <= days; d++) {
        int m = money - d / 3 * 200 - d % 3 / 2 * 150 - d % 3 % 2 * 100;
        if (m <= 0)
            break;
        memset(f, 0, sizeof(f));
        for (int i{0}; i < n; i++) {
            if (limited[i]) {
                for (int j{d * 24}; j >= 0; j--) {
                    for (int k{m}; k >= 0; k--) {
                        if (j - t[i] >= 0 && k - c[i] >= 0)
                            f[j][k] = max(f[j][k], f[j - t[i]][k - c[i]] + h[i]);
                        ans = max(ans, f[j][k]);
                    }
                }
            } else {
                for (int j{0}; j <= d * 24; j++) {
                    for (int k{0}; k <= m; k++) {
                        if (j - t[i] >= 0 && k - c[i] >= 0)
                            f[j][k] = max(f[j][k], f[j - t[i]][k - c[i]] + h[i]);
                        ans = max(ans, f[j][k]);
                    }
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}