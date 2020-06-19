#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

int a[102]{};

int n, k;
int cnt;
int ans;
void dfs(int money, int t) {
    if (t > n) {
        if (money == 0) {
            ans = min(ans, cnt);
        }
        return;
    }
    int newm{money};
    int ocnt{cnt};
    while (newm >= 0) {
        dfs(newm, t + 1);
        newm -= a[t];
        cnt++;
        if(cnt >= ans) break;
    }
    cnt = ocnt;
}

int main() {
    while (cin >> n >> k, n) {
        for (int i{1}; i <= n; i++) {
            cin >> a[i];
        }
        ans = numeric_limits<int>::max();
        cnt = 0;
        dfs(k, 1);
        if (ans == numeric_limits<int>::max())
            cout << "-1" << endl;
        else
            cout << ans << endl;
    }
}