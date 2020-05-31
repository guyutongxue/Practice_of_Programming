// DP

#include <math.h>
#include <memory.h>
#include <stdlib.h>

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <set>
#include <string>
using namespace std;

int m, n, s;
int limit[105][3], unlimit[105][3];
int sumlimi = 0, sumun = 0;
int dp[2][2405][1005];  // 0:limit 1:unlimit time money
int maxday;
int ans = 0;

void solve() {
    for (int day = 1; day <= maxday; day++) {
        memset(dp, 0, sizeof(int) * 2 * 2405 * 1005);
        int money = s;
        money -= day / 3 * 200 + (day % 3 / 2 * 150) + (day % 3 % 2 * 100);
        int time = 24 * day;
        for (int i = 1; i <= sumlimi; i++)
            for (int j = time; j >= 1; j--)
                for (int k = money; k >= 0; k--)
                    if (k >= limit[i][1] && j >= limit[i][2])
                        dp[0][j][k] =
                            max(dp[0][j][k], dp[0][j - limit[i][2]][k - limit[i][1]] + limit[i][0]);
        for (int i = 1; i <= sumun; i++)
            for (int j = 1; j <= time; j++)
                for (int k = 0; k <= money; k++)
                    if (k >= unlimit[i][1] && j >= unlimit[i][2])
                        dp[1][j][k] = max(dp[1][j][k], dp[1][j - unlimit[i][2]][k - unlimit[i][1]] +
                                                           unlimit[i][0]);
        for (int i = 0; i <= time; i++)
            for (int j = 0; j <= money; j++)
                ans = max(ans, dp[0][i][j] + dp[1][time - i][money - j]);
    }
    printf("%d\n", ans);
}

int main() {
    scanf("%d%d%d", &m, &n, &s);
    int _s = s;
    maxday += _s / 200 * 3;
    _s %= 200;
    maxday += _s / 150 * 2;
    _s %= 150;
    maxday += _s / 100;
    maxday = min(maxday, m);
    for (int i = 1; i <= n; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        string ch;
        cin >> ch;
        if (ch == "limited") {
            limit[++sumlimi][0] = a;
            limit[sumlimi][1] = b;
            limit[sumlimi][2] = c;
        } else {
            unlimit[++sumun][0] = a;
            unlimit[sumun][1] = b;
            unlimit[sumun][2] = c;
        }
    }
    solve();
    return 0;
}