#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

int w[1002];
int n, m;

int getM(int x) {
    int res{0};
    for (int i{1}; i <= n; i++) {
        res += ceil(1. * w[i] / x);
    }
    return res;
}

int main() {
    cin >> n >> m;
    for (int i{1}; i <= n; i++) {
        cin >> w[i];
    }
    int l{1};
    int r{10000000};
    while (l < r) {
        int mid{(l + r) / 2};
        if (getM(mid) > m) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    cout << l << endl;
}