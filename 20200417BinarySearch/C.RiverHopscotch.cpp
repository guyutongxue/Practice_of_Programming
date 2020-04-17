// NOIp 2015 J T4

#include <iostream>
#include <limits>
using namespace std;

int length, n, m;
int a[50002] = {};

/**
 * @brief 返回固定长度下，“落脚”的总石子数
 * 
 * @param x 最短的跳跃距离
 * @return int 可以落脚的总石子数，不计岸边
 */
int getResult(int x) {
    int num = 0;
    int pos = 0;
    for (int i = 1; i <= n + 1; ++i) {
        if (a[i] - a[pos] >= x) {
            num++;
            pos = i;
        }
    }
    return num;
}

int main() {
    cin >> length >> n >> m;
    int l = 0, r = length, ans;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    a[0] = 0;
    a[n + 1] = length;
    // 需要取等号。因为 ans 需要在循环内更新。
    while (l <= r) {
        int mid = (l + r) / 2;
        // n - m 即要求的最少剩余石子数
        if (getResult(mid) <= n - m) {
            // 如果所需的比最少剩余还要少，说明这种情形是不合要求的
            // 需要让跳跃的最短长度小一点，这样才能增加剩余石子数
            // 不能取 r = mid 的原因是 mid 已经不符合要求了
            r = mid - 1;
        } else {
            // 这种情形是符合题目要求的，但是需要检查有没有更优的解
            // 即是否能有更长的跳跃长度，使得剩余石子数仍然大于题目要求的最小值
            // 但是需要记录一下当前的答案
            l = mid + 1;
            ans = mid;
        }
    }
    cout << ans << endl;
}