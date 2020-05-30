// Bailian 4129, DFS + cut

#include <cstdio>
#include <string>
#include <memory.h>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include<queue>
#include <set>
using namespace std;

int dp[10001][4];//0：放的时候两边都没放，1：放的时候左边已放，2：放的时候右边已放，3：放的时候两边都放了
int a[10001], b[10001], c[10001];
int n;

int main()
{
    scanf("%d", &n);
    for (int j = 1; j <= n; j++)
        scanf("%d", &a[j]);
    for (int j = 1; j <= n; j++)
        scanf("%d", &b[j]);
    for (int j = 1; j <= n; j++)
        scanf("%d", &c[j]);
    dp[1][0] = a[1];
    dp[1][1] = -10000;
    dp[1][2] = b[1];
    dp[1][3] = -10000;
    for (int i = 2; i <= n; i++) {
        dp[i][0] = max(dp[i - 1][2], dp[i - 1][3]) + a[i];
        dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]) + b[i];
        dp[i][2] = max(dp[i - 1][2], dp[i - 1][3]) + b[i];
        dp[i][3] = max(dp[i - 1][0], dp[i - 1][1]) + c[i];
    }
    printf("%d\n", max(dp[n][0], dp[n][1]));
    return 0;
}