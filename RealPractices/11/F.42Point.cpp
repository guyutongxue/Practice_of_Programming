// DP

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

set<int> dp[7][7];
int num[7],n;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &num[i]);
        dp[i][i].insert(num[i]);
    }
    int sum = 1;
    for (int i = 2; i <= n; i++)
        sum += i;
    for (int _case = 1; _case <= sum; _case++) {
        next_permutation(num, num + n);
        for(int i=2;i<=n;i++)
            for (int j = 1; j <= n - i + 1; j++) {
                for (int k = j; k <= j+i-2; k++) {
                    for(auto ii=dp[j][k].begin();ii!=dp[j][k].end();ii++)
                        for (auto jj = dp[k + 1][j + i - 1].begin(); jj != dp[k + 1][j + i - 1].end(); jj++) {
                            dp[j][j + i - 1].insert(*ii + *jj);
                            dp[j][j + i - 1].insert(abs(*ii - *jj));
                            dp[j][j + i - 1].insert(*ii * *jj);
                            if (*jj != 0 && (*ii / (*jj)*(*jj)) == *ii)
                                dp[j][j + i - 1].insert(*ii / (*jj));
                        }
                }
            }
    }
    if (dp[1][n].find(42) != dp[1][n].end())
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}