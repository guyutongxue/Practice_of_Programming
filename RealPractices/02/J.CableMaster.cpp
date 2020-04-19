#include <algorithm>
#include <iomanip>
#include <iostream>
using namespace std;

double a[10002];
int n, k;

bool check(int x) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += a[i] / x;
    }
    return sum >= k;
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        double v;
        cin >> v;
        a[i] = v * 100.0;
    }
    sort(a + 1, a + 1 + n);
    int l = 1, r = a[n];
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid))
            l = mid + 1;
        else
            r = mid - 1;
    }
    cout << fixed << setprecision(2) << 1. * r / 100.0 << endl;
}