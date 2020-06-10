// Bailian 4150, DP

#include <algorithm>
#include <iostream>
using namespace std;

enum { EMPTY, LEFT, RIGHT, BOTH };

/**
 * f: DP
 * [i: the number of seat][j: the status when occupying this seat]
 * Returns: The maximum result when seat 1 ~ i is occupied, while
 *          the status of occupying seat i is ensured.
 * 
 * Mention that this DP is about sequence. So the exact meaning of j is:
 * f[i][LEFT] or f[i][BOTH]: Seat (i - 1) is occupied already. So Seat i is occupied _after_ (i - 1)
 * f[i][RIGHT] or f[i][EMPTY]: Seat (i - 1) is empty. So seat i is occupied _before_ (i - 1)
 * 
 * That's means, when j is LEFT or BOTH, the (i - 1) must be EMPTY or LEFT.
 * That's because i is ocuppied after (i - 1), so when (i - 1) is occupied the position i is empty.
 * Also you can find that when j is RIGHT or EMPTY, the (i - 1) must be RIGHT or BOTH.
 * 
 * Formula:
 * f[i][EMPTY] = max(f[i - 1][RIGHT], f[i - 1][BOTH]) + a[i];
 * f[i][LEFT] = max(f[i - 1][EMPTY], f[i - 1][LEFT]) + b[i];
 * f[i][RIGHT] = max(f[i - 1][RIGHT], f[i - 1][BOTH]) + b[i];
 * f[i][BOTH] = max(f[i - 1][EMPTY], f[i - 1][LEFT]) + c[i];
 */
int f[10001][4]{};

int a[10001]{}, b[10001]{}, c[10001]{};

int main() {
    int n;
    cin >> n;
    for (int i{1}; i <= n; i++) {
        cin >> a[i];
    }
    for (int i{1}; i <= n; i++) {
        cin >> b[i];
    }
    for (int i{1}; i <= n; i++) {
        cin >> c[i];
    }
    f[1][EMPTY] = a[1];
    f[1][LEFT] = -1;
    f[1][RIGHT] = b[1];
    f[1][BOTH] = -1;
    for (int i{2}; i <= n; i++) {
        f[i][EMPTY] = max(f[i - 1][RIGHT], f[i - 1][BOTH]) + a[i];
        f[i][LEFT] = max(f[i - 1][EMPTY], f[i - 1][LEFT]) + b[i];
        f[i][RIGHT] = max(f[i - 1][RIGHT], f[i - 1][BOTH]) + b[i];
        f[i][BOTH] = max(f[i - 1][EMPTY], f[i - 1][LEFT]) + c[i];
    }
    cout << max(f[n][EMPTY], f[n][LEFT]) << endl;
}