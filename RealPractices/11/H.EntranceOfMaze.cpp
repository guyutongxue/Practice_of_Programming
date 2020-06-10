#include <cstring>
#include <iostream>
using namespace std;
int s, n;
int cnt[45]{};
bool a[45][45]{};
void fill(int x, int y, int d, bool val) {
    for (int i{x}; i < x + d; i++) {
        for (int j{y}; j < y + d; j++) {
            a[i][j] = val;
        }
    }
}
bool dfs(int x, int y) {
    if (a[x][y]) {
        return (y == s - 1) ? ((x == s - 1) ? true : dfs(x + 1, 0)) : dfs(x, y + 1);
    }
    bool res{false};
    for (int d{1}; !res; d++) {
        if (y + d > s || x + d > s || a[x][y + d - 1])
            break;
        if (!cnt[d])
            continue;
        cnt[d]--;
        fill(x, y, d, true);
        res = res || dfs(x, y);
        fill(x, y, d, false);
        cnt[d]++;
    }
    return res;
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> s >> n;
        memset(cnt, 0, sizeof(cnt));
        for (int i{0}; i < n; i++) {
            int tmp;
            cin >> tmp;
            cnt[tmp]++;
        }
        if (s > 40)
            cout << "NO" << endl;
        else
            cout << (dfs(0, 0) ? "YES" : "NO") << endl;
    }
}