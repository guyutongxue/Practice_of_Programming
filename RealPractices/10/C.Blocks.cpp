// POJ 1390, luogu.org: UVA10559

// Absolutely this a very hard problem in current status. (In luogu.org, it's rank as "NOI-".)

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

// The algorithm here called "Interval DP".

/**
 * f: DP
 * [i: begin-pos][j: end-pos][k: an extra parameter, see below]
 * Returns:
 *     The maximum score when erasing all blocks from pos i to pos (j + k).
 *     There are k extra blocks in the right side of pos j,
 *     which has the same color as block in pos j.
 *    ----+---+---+---+-------+---+---+---+-------+---+----
 *    ... | a | b | c |  ...  | x | x | x |  ...  | x | ...
 *    ----+---+---+---+-------+---+---+---+-------+---+----
 *          ^                   ^  \--------v--------/
 * position i          position j  k same color blocks
 *
 * Formula:
 * // Consider erasing block in pos j. There are two method to do:
 * // 1. Remove block j with that k blocks together.
 * //    This will remove (k + 1) blocks in the end of sequence.
 * // 2. If there exists blocks which has the same color as block j
 * //    at position p, as the figure below:
 * // ----+---+-------+---+---+-------+---+---+---+---+-------+---+----
 * // ... | a |  ...  | x | d |  ...  | e | x | x | x |  ...  | x | ...
 * // ----+---+-------+---+---+-------+---+---+---+---+-------+---+----
 * //       ^           ^                   ^  \--------v--------/
 * //   pos i       pos p (same color)  pos j  k same color blocks
 * //    We can remove the blocks between pos (p + 1) from (j - 1),
 * //    then the problem turns into:
 * // ----+---+-------+---+---+---+---+-------+---+----
 * // ... | a |  ...  | x | x | x | x |  ...  | x | ...
 * // ----+---+-------+---+---+---+---+-------+---+----
 * //       ^           ^   ^  \--------v--------/
 * //       i           p   j  k same color blocks   (Here letters represent old pos)
 * //                      \------ now k+1 ------/
 * //     ...which can be described as f[i][p][k + 1].
 *
 * f[i][j][k] = max (
 *     f[i][j - 1][0] + (k + 1) * (k + 1),                // the first method
 *     max [                                              // the second method
 *         f[p + 1][j - 1][0] + f[i][p][k + 1],
 *         for p from i to j - 1, requires a[p] == a[j]   // here a[i] is the color of pos i
 *     ]
 * );
 * 
 * Looping Sequence: 
 * for i from n to 1 (because i need requisites higher then it)
 * for j from 1 to i
 * for k from 0 to dis[j] // dis[j] is the maximum count of blocks which has same color as j
 */
int f[205][205][205] = {};

/**
 * a: data 
 * a[position]
 * Returns: the color of block in that position.
 */
int a[201] = {};

/**
 * dis: requisite
 * dis[position]
 * Returns: how many blocks in the right side of j has the same color
 */
int dis[201] = {};

int main() {
    int t;
    scanf("%d", &t);
    for (int cases = 1; cases <= t; ++cases) {
        int n;
        scanf("%d", &n);
        memset(f, 0, sizeof(f));
        memset(dis, 0, sizeof(dis));
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        for (int i = n; i >= 0; i--)
            for (int j = i + 1; j <= n; j++)
                if (a[i] == a[j])
                    dis[i]++;
        for (int i = n; i >= 0; i--) {
            for (int j = i; j <= n; j++) {
                for (int k = 0; k <= dis[j]; k++) {
                    f[i][j][k] = f[i][j - 1][0] + (k + 1) * (k + 1);
                }
                for (int p = i; p < j; p++) {
                    if (a[p] == a[j]) {
                        for (int k = 0; k <= dis[j]; k++) {
                            f[i][j][k] = max(f[i][j][k], f[p + 1][j - 1][0] + f[i][p][k + 1]);
                        }
                    }
                }
            }
        }
        printf("Case %d: %d\n", cases, f[1][n][0]);
    }
    return 0;
}