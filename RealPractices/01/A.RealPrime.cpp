#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
bool isPrime(int x) {
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0)
            return false;
    }
    return true;
}

int rever(int x) {
    int bit[7] = {}, i = 0;
    do {
        bit[i++] = x % 10;
    } while (x /= 10);
    int res = 0, total = i;
    while (i) {
        (res *= 10) += bit[total - (i--)];
    }
    return res;
}

int main() {
    int m, n;
    cin >> m >> n;
    bool isFirst = true;
    for (int i = max(m, 2); i <= n; ++i) {
        if (isPrime(i) && isPrime(rever(i))) {
            cout << (isFirst ? isFirst = false, "" : ",") << i;
        }
    }
    if (isFirst)
        cout << "No" << endl;
}