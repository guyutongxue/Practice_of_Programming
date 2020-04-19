#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    int maxi = pow(n, 1. / 3);
    int ans = numeric_limits<int>::max();
    // +1 prevent some cast mistake
    for (int i = 1; i <= maxi + 1; i++) {
        if (n % i != 0)
            continue;
        int p = n / i;
        int maxj = sqrt(p);
        for (int j = i; j <= maxj + 1; j++) {
            if (p % j != 0)
                continue;
            int k = p / j;
            ans = min(ans, i * j + j * k + i * k);
        }
    }
    cout << 2 * ans << endl;
}