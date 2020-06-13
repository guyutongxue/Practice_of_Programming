// I have to admire that this method is so genius.
// I can't find it on my own.
// Thanks studnent No. 1900011**3

#include <iomanip>
#include <iostream>
using namespace std;
int a[210]{};
char o[210]{};
double p[210]{};

/**
 * @brief This function calculate the result's certain bit's change.
 * It's hard to calculate &, | and ^'s expectation, but calculating each bit is easier.
 * For example, if &'s operand is bit 0, then the expectation goes to 0.
 * Otherwise, the expectation keep as before.
 *
 * @param e The result before
 * @param o Operator
 * @param rhs The rhs-operand, which is a bit
 * @return double The result after operate this operand
 */
double calc(double e, char o, bool rhs) {
    switch (o) {
        case '^': return rhs ? 1. - e : e;  // rhs is 1 will reverse the expectation.
        case '|': return rhs ? 1. : e;
        case '&': return rhs ? e : 0.;
        default: return 0.;
    }
}
int main() {
    int n;
    for (int t{1}; cin >> n; t++) {
        double ans{0.};
        for (int i{0}; i <= n; i++) {
            cin >> a[i];
        }
        for (int i{1}; i <= n; i++) {
            cin >> o[i];
        }
        for (int i{1}; i <= n; i++) {
            cin >> p[i];
        }

        for (int i{0}; i <= 20; i++) {
            // The expectation for bit i.
            double e{0. + ((a[0] >> i) & 1)};
            for (int j = 1; j <= n; j++) {
                // p[j] is the possibility disappearing, while e keeps it's value;
                // (1 - p[j]) is the possibility doing the calculate
                e = e * p[j] + (1 - p[j]) * calc(e, o[j], (a[j] >> i) & 1);
            }
            ans += (1 << i) * e;
        }
        cout << "Case " << t << ": \n" << fixed << setprecision(6) << ans << endl;
    }
}
