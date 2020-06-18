#include <algorithm>
#include <iostream>
using namespace std;

int a[1002]{};
int lds[1002]{};
int lis[1002]{};
int main() {
    int n;
    cin >> n;
    for (int i{1}; i <= n; i++) {
        cin >> a[i];
    }
    for (int i{1}; i <= n; i++) {
        lds[i] = 1;
        for (int j{1}; j < i; j++) {
            if (a[i] <= a[j]) {
                lds[i] = max(lds[i], lds[j] + 1);
            }
        }
    }
    for (int i{n}; i >= 1; i--) {
        lis[i] = 1;
        for (int j{n}; j > i; j--) {
            if (a[i] >= a[j]) {
                lis[i] = max(lis[i], lis[j] + 1);
            }
        }
    }
    int ans{-1};
    for (int i{1}; i <= n; i++) {
        int lh{-1}, rh{-1};
        for (int j{1}; j <= i; ++j) {
            lh = max(lh, lds[j]);
        }
        for (int j{i + 1}; j <= n; ++j) {
            rh = max(rh, lis[j]);
        }
        ans = max(ans, lh + rh);
    }
    cout << ans << endl;
}