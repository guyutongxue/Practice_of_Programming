#include <iostream>
#include <limits>
using namespace std;

int m, n, ans{numeric_limits<int>::max()};
int a[18]{};

// Capacity left
int bag[18]{};

/**
 * @brief 
 * 
 * @param x Current No. of object
 * @param sum How many bag is using now
 */
void dfs(int x, int sum) {
    if (sum >= ans) // cut
        return;
    if (x == n) {
        ans = min(ans, sum);
        return;
    }
    // insert object into used bags...
    for (int i{0}; i < sum; ++i) {
        if (bag[i] >= a[x]) {
            bag[i] -= a[x];
            dfs(x + 1, sum);
            bag[i] += a[x];
        }
    }
    // or create a new bag
    bag[sum] -= a[x];
    dfs(x + 1, sum + 1);
    bag[sum] += a[x];
}
int main() {
    cin >> n >> m;
    for (int i{0}; i < n; ++i) {
        cin >> a[i];
        bag[i] = m;
    }
    dfs(0, 1);
    cout << ans << endl;
    return 0;
}