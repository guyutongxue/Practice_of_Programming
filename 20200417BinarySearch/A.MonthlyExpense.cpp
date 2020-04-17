// POJ3273

#include <algorithm>
#include <iostream>
#include <limits>
using namespace std;

int n, m;
int a[100002] = {};

bool getResult(int exp) {
    int i = 1;  // day
    int j = 0;  // 'fojo' month
    while (i <= n) {
        int sum = 0;
        while (sum + a[i] <= exp && i <= n)
            sum += a[i++];
        j++;
        if (j > m)
            return false;
    }
    return true;
}

int main() {
    cin >> n >> m;
    int l = -1, r = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        l = max(l, a[i]);
        r += a[i];
    }
    while (l < r) {
        int mid = (l + r) / 2;
        if (getResult(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << r << endl;
}