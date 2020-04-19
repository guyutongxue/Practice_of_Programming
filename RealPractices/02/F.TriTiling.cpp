#include <iostream>
using namespace std;
int calc(int n) {
    if (n == 0)
        return 1;
    if (n == 1)
        return 0;
    if (n == 2)
        return 3;
    int sum = 3 * calc(n - 2);
    for (int i = 4; i <= n; i += 2) {
        sum += 2 * calc(n - i);
    }
    return sum;
}
int main() {
    int n;
    while (cin >> n, n != -1) {
        cout << calc(n) << endl;
    }
}