#include <iostream>
using namespace std;

int a[1001];

/**
 * f: DP
 * [first i number][j as the sum]
 * Returns: how many solution
 * 
 * Formula:
 * f[i][j] =
 *     (j > a[i] ? f[i - 1][j - a[i]] : 0) +  // take this number
 *     f[i - 1][j]                            // or don't take this number
 * ;
 *  
 */
long long f[1001][1001] = {};

int main() {
    int n, t;
    cin >> n >> t;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        f[i][0] = 1;
    }
    f[0][0] = 1;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= t; j++)
            if (j < a[i])
                f[i][j] = f[i - 1][j];
            else
                f[i][j] = f[i - 1][j] + f[i - 1][j - a[i]];
    cout << f[n][t] << endl;
}