#include <iostream>
using namespace std;
int lis[1002], lds[1002];
int a[1002];
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    // Solve LIS
    for (int i = 1; i <= n; i++) {
        lis[i] = 1;
        for (int j = 1; j <= i; j++) {
            if (a[i] > a[j])
                lis[i] = max(lis[i], lis[j] + 1);
        }
    }
    // Based on the LIS result, solve LDS
    // (Longest Decrease Subsequence)
    for (int i = 1; i <= n; i++) {
        lds[i] = 1;
        for (int j = 1; j <= i; j++) {
            if (a[i] < a[j])
                lds[i] = max(lds[i], max(lis[j], lds[j]) + 1);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max({ans, lis[i], lds[i]});
    }
    cout << ans << endl;
    return 0;
}