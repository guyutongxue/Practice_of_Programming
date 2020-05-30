// dfs

#include <cstdio>
#include <string>
#include <memory.h>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include<queue>
#include <vector>
using namespace std;

const double eps = 1e-6;
int s,time0;
vector<int> solution;
bool flag=false;

bool is_equal(double a) {
    if (a <= 1 + eps && a >= 1 - eps)
        return true;
    return false;
}

void dfs(double sum,int now,int left) {
    if (flag)
        return;
    if (sum + 1 / (double)left > 1 + eps)
        return;
    if (is_equal(sum + 1 / (double)left)) {
        flag = 1;
        solution.push_back(left);
        return;
    }
    for (int i = now; i < left-1; i++) {
        solution.push_back(i);
        dfs(sum + 1 / (double)i, i, left - i);
        if (flag)
            return;
        solution.pop_back();
    }
}


int main()
{
    int t;
    scanf("%d", &t);
    while (t--) {
        flag = false;
        solution.clear();
        scanf("%d", &time0);
        dfs(0, 1, time0);
        vector<int>::iterator i1 = solution.begin(),i2=solution.end();
        if (flag)
        {
            printf("%d", solution.size());
            for (; i1 != i2; i1++)
                printf(" %d", *i1);
            printf("\n");
        }
        else
            printf("-1\n");
    }
    return 0;
}