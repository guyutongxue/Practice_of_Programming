// Copied from IC-A/P2-6/2

#include <algorithm>
#include <iomanip>
#include <iostream>
using namespace std;
double b[1002];
int main() {
    while (true) {
        int n;
        cin >> n;
        if (cin.eof())
            break;
        for (int i = 1; i <= n; i++) {
            cin >> b[i];
        }
        sort(b + 1, b + n + 1);
        double s = 0.;
        for (int i = 1; i < n; i++) {
            s += b[i];
        }
        if (s <= b[n]) {
            cout << fixed << setprecision(1) << s << endl;
        } else {
            cout << fixed << setprecision(1) << (s + b[n]) / 2 << endl;
        }
    }
    return 0;
}