#include <iomanip>
#include <iostream>
using namespace std;
constexpr double EPS = 1e-9;

double f(double x) {
    return x * x * x * x * x - 15 * x * x * x * x + 85 * x * x * x - 225 * x * x + 274 * x - 121;
}

int main() {
    double l = 1.5;
    double r = 2.4;
    while (r - l > EPS) {
        double mid = (r + l) / 2;
        if (f(mid) > 0)
            l = mid;
        else
            r = mid;
    }
    cout << fixed << setprecision(6) << l << endl;
}