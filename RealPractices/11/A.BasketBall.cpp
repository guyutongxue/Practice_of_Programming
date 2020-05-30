// Enum


#include <cstdio>
#include <string>
#include <memory>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

int main()
{
    int t;
    scanf("%d", &t);
    while (t--) {
        char info[5][5];
        int point[5] = { 0 };
        for (int i = 1; i <= 4; i++)
            for (int j = 1; j <= 4; j++)
            {
                cin >> info[i][j];
                if (j > i)
                {
                    if (info[i][j] == 'W')
                        point[i]++;
                    else if (info[i][j] == 'L')
                        point[j]++;
                }
            }
        int notdefined[4][3],h=1;
        for(int i=1;i<=3;i++)
            for(int j=i+1;j<=4;j++)
                if (info[i][j] == '?') {
                    if (i == 1)
                        point[1]++;
                    else if (point[i] > point[1])
                        point[i]++;
                    else if (point[j] > point[1])
                        point[j]++;
                    else
                        notdefined[h][0] = i,notdefined[h][1]=j,notdefined[h++][2]=0;
                }
        int _point[5], ans = 4;
        for (int i = 1; i <=1<<(h-1); i++) {
            int tmp = 1;
            notdefined[1][2]++;
            while (notdefined[tmp][2] > 1) {
                notdefined[tmp][2] = 0;
                tmp++;
                notdefined[tmp][2]++;
            }
            for (int j = 1; j <= 4; j++)
                _point[j] = point[j];
            for (int j = 1; j <= h - 1; j++) {
                if (notdefined[j][2] == 1)
                    _point[notdefined[j][0]]++;
                else
                    _point[notdefined[j][1]]++;
            }
            int _ans = 1;
            for (int i = 2; i <= 4; i++)
                if (_point[i] > _point[1])
                    _ans++;
            ans = min(_ans, ans);
        }
        printf("%d\n", ans);
    }
    return 0;
}