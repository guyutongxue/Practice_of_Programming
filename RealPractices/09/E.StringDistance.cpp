// POJ 4007

#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
/**
 * f: DP
 * [the endpos of string a][the endpos of string b]
 * return: the similarity (minimize)
 *
 * Formula:
 * f[i][j] =
 *     pattern[i] == dest[j] ?
 *         f[i-1][j-1]      // no need to change
 *     :
 *         min(
 *             f[i][j-1],   // insert or delete
 *             f[i-1][j],   // insert or delete
 *             f[i-1][j-1]  // modify
 *         ) + 1
 * ;
 *
 */
int f[1002][1002];
int main() {
    int n;
    cin >> n;
    while (n--) {
        string a, b;
        cin >> a >> b;
        memset(f, 0, sizeof(f));
        int la = a.length();
        int lb = b.length();
        for (int i = 0; i <= la; i++) {
            f[i][0] = i;
        }
        for (int i = 0; i <= lb; i++) {
            f[0][i] = i;
        }
        for (int i = 1; i <= la; i++) {
            for (int j = 1; j <= lb; j++) {
                f[i][j] =
                    (a[i - 1] == b[j - 1] ? f[i - 1][j - 1]
                                          : min({f[i - 1][j - 1], f[i][j - 1], f[i - 1][j]}) + 1);
            }
        }
        // for (int i = 0; i <= la; i++) {
        //     for (int j = 0; j <= lb; j++) {
        //         cout << f[i][j];
        //     }
        //     cout << endl;
        // }
        cout << f[la][lb] << endl;
    }
    return 0;
}