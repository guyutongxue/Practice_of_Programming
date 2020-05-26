// ybt 1302

#include <cstring>
#include <iostream>
using namespace std;

/**
 * f: DP
 * [i: position of store][j: whether steal it (0 or 1)]
 * Returns: How many money did Fu get from store 1 to store i
 * 
 * Formula:
 * // If don't steal this store, the money keeps the max of last. 
 * f[i][0] = max(f[i - 1][0], f[i - 1][1]);
 * // If steal this store, the last store mustn't stole before.
 * f[i][1] = f[i - 1][0] + a[i]; 
 * 
 */
int f[100001][2] = {};

/**
 * a: data
 * [i]
 * Returns value of store i.
 */
int a[100001] = {};

int main() {
    int n, t;  //店铺量，数据组数
    cin >> t;
    while (t--) {
        memset(f, 0, sizeof(f));
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        f[1][0] = 0;
        f[1][1] = a[1];
        for (int i = 2; i <= n; i++) {
            f[i][0] = max(f[i - 1][0], f[i - 1][1]);
            f[i][1] = f[i - 1][0] + a[i];
        }
        cout << max(f[n][0], f[n][1]) << endl;
    }
    return 0;
}