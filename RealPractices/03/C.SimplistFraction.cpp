#include <iostream>
#if __cplusplus >= 201703L
#include <numeric>
// 有现成的就不要造轮子
using std::gcd;
#else
#include <algorithm>
int gcd(int a, int b) {
    if (a < b)
        std::swap(a, b);
    int r = a % b;
    while (r != 0) {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}
#endif
using std::cin;
using std::cout;
using std::endl;
int a[605];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (gcd(a[i], a[j]) == 1)
                cnt++;
        }
    }
    cout << cnt << endl;
}