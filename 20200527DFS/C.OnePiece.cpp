#include <algorithm>
#include <iostream>
using namespace std;

const int INF = 99999;

/**
 * a: Data
 * [i][j]
 * Returns: time to travel from island #i to #j
 *
 */
int a[20][20];

/**
 * f: DP
 * [i: state][j: island no.]
 * Returns: The minist time in "state i" (see below), arriving at island #j.
 * 
 * About state:
 * Use binary to store a state, stands for those visited islands.
 * 0b000...1000101
 * here you see the each bit represents whether visited.
 * The bit 0 is 1 means island #0 is visited;
 * The bit 1 is 0 means island #1 not visited yet;
 * etc.
 * 
 * Formula:
 * f[i][j] = min[
 *     f[i ^ (1 << k)][k] + a[k][j], // i ^ (1 << k) means removing bit k from state i
 *     for k from 1 to n - 1,
 *     requires (i & 1 << k)
 * ];
 * 
 * 
 */
int f[1 << 16][20];
int n;

int solve(int32_t state, int land) {
    if (f[state][land] != INF ||
        state == 0 && land == 0)  // already visited or it's the start point
        return f[state][land];
    if (land == 0)  // Shouldn't visit start point after visiting some island
        return INF;
    for (int i = 0; i < n; i++) {
        if (state & (1 << i))
            f[state][land] = min(f[state][land], solve(state ^ (1 << i), i) + a[i][land]);
    }
    return f[state][land];
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= 1 << n; i++) {
        for (int j = 0; j < n; j++) {
            f[i][j] = INF;
        }
    }
    cout << solve((1 << (n - 1)) - 1, n - 1) << endl;
    return 0;
}