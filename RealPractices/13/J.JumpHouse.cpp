#include <iostream>
using namespace std;
int n, m;
bool a[30]{};
bool dfs(int x, int ans, int tmp) {
    if (tmp > ans)
        return false;
    a[tmp] = false;
    if (3 * x == m)
        return true;
    if (!dfs(3 * x, ans, tmp + 1)) {
        a[tmp] = true;
        if (x / 2 == m)
            return true;
        return dfs(x / 2, ans, tmp + 1);
    } else
        return true;
}
int main() {
    while (cin >> n >> m, n) {
        int ans{1};
        while (!dfs(n, ans, 1)) {
            ans++;
        }
        cout << ans << endl;
        for (int i{1}; i <= ans; i++) {
            cout << "HO"[a[i]];
        }
        cout << endl;
    }
}