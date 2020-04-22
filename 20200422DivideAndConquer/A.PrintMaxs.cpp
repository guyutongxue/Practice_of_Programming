#include <algorithm>
#include <iostream>
using namespace std;
int a[100002];
int main() {
    int n, k;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cin >> k;
    sort(a + 1, a + n + 1, [](int a, int b) { return a > b; });
    for (int i = 1; i <= k; i++) {
        cout << a[i] << endl;
    }
    return 0;
}