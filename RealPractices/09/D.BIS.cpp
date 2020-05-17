#include <algorithm>
#include <iostream>
using namespace std;

int a[1002] = {};
int f[1002] = {};

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        int temp = 0;
        for (int j = 0; j < i; ++j) {
            if (a[i] > a[j])
                temp = max(temp, f[j]);
        }
        f[i] = a[i] + temp;
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, f[i]);
    }
    cout << ans << endl;
}