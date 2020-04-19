// Copied from IC-A/P3-3/4
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
int count(int x, int sup) {
    if (x == 1)
        return 1;
    int sum = 0;
    for (int i = min(x, sup); i > 1; i--) {
        if (x % i == 0)
            sum += count(x / i, i);
    }
    return sum;
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        int x;
        cin >> x;
        cout << count(x, x) << endl;
    }
    return 0;
}