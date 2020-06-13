// CJOJ 2723

#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

/**
 * f0, f1: DP
 * [i: length of sequence]
 * Returns:
 *     f0: Minimum changes to all-zero-seq (000.....0) with length i
 *     f1: Minimum changes to non-all-zero-seq (000....0111...1) with total length i
 *
 * Formula:
 * f0[i] =
 *     s[i] == '0' ?
 *          f0[i - 1]     // no need to change, just equals to last all-zero-seq
 *     :
 *          f0[i - 1] + 1 // need to change s[i] from '1' to '0'
 * ;
 *
 * f1[i] =
 *     s[i] == '0' ?
 *          min(
 *             f0[i - 1]
 *             f1[i - 1]
 *          ) + 1           // same as below, but need to change '0' to '1'
 *     :
 *          min(
 *              f0[i - 1],  // all-zero-seq before, means the result is "000...001"
 *              f1[i - 1]   // non-all-zero-seq before, means the result is "00..011...1"
 *          )
 * ;
 *
 */
int f0[1010];
int f1[1010];

int main() {
    int t;
    cin >> t;
    while (t--) {
        char s[1005];
        cin >> s;
        memset(f0, 0, sizeof(f0));
        memset(f1, 0, sizeof(f1));
        int len{strlen(s)};
        if (s[0] == '0') {
            f0[0] = 0;
            f1[0] = 1;
        } else {
            f0[0] = 1;
            f1[0] = 0;
        }
        for (int i{1}; i < len; ++i) {
            if (s[i] == '0') {
                f0[i] = f0[i - 1];
                f1[i] = min(f0[i - 1], f1[i - 1]) + 1;
            } else {
                f0[i] = f0[i - 1] + 1;
                f1[i] = min(f0[i - 1], f1[i - 1]);
            }
        }
        cout << min(f1[len - 1], f0[len - 1]) << endl;
    }
}