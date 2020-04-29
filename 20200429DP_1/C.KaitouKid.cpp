#include <algorithm>
#include <iostream>
using namespace std;

/**
 * @brief 计算一个序列的最长上升子序列（LIS）。
 * 
 * @tparam T 
 * @param arr 要计算的序列。
 * @param n 序列长度。
 * @return int 最长上升子序列的长度。
 */
template<typename T>
int lis(const T* arr, int n) {
    T* dp = new T[n];
    for (int i = 0; i < n; ++i) {
        dp[i] = 1;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (arr[j] < arr[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    int ans = -1;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, dp[i]);
    }
    delete[] dp;
    return ans;
}

int main() {
    int k;
    cin >> k;
    while (k--) {
        int n;
        int a[102];
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        int lres = lis(a, n);
        reverse(a, a+n);
        int rres = lis(a, n);
        cout << max(lres, rres) << endl;
    }
}