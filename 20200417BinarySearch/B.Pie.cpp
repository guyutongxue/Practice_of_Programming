
#include <algorithm>
#include <iomanip>
#include <iostream>
#if __cplusplus >= 202002L
#include <numbers>
const double PI = std::numbers::pi;
#else
// nonstandard usage
#define _USE_MATH_DEFINES
#include <cmath>
const double PI = M_PI;
#endif
using namespace std;

const double EPS = 1e-6;
int n, f;
double a[10002] = {};

bool getResult(double x) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        cnt += static_cast<int>(a[i] / x);
    }
    return cnt >= f;
}

int main() {
    cin >> n >> f;
    f++;
    double l = 0., r = 0., mid;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] *= a[i] * PI;
        r += a[i];
    }
    r /= f;
    while (r - l > EPS) {
        mid = (l + r) / 2;
        if (getResult(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << fixed << setprecision(3) << l << endl;
}