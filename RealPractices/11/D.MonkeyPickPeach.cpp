#include <cstdio>
#include <string>
#include <memory.h>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include<queue>
using namespace std;

int info[105][2];
int hon,sum,ans;

int main()
{
    while (cin >> hon)
    {
        if (hon == -1)break;
        sum = 0, ans = 0;
        int p = 1;
        while (1) {
            scanf("%d%d", &info[p][0], &info[p][1]);
            if (info[p][0] == -1)break;
            sum++;
            p++;
        }
        for (int i = 1; i <= sum; i++) {
            int _hon = hon, peach = 0;
            for (int j = i; j <= sum; j++) {
                _hon -= info[j][1];
                if (_hon < 0)
                    break;
                peach += info[j][0];
            }
            ans = max(ans, peach);
        }
        printf("%d\n", ans);
    }
    return 0;
}