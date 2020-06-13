#include <iostream>
using namespace std;
long long f[55]{1, 1};
int main() {
    for (int i{2}; i <= 50; ++i) {
        f[i] = f[i - 2] + f[i - 1];
    }
    int n;
    cin >> n;
    for (int i{0}; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        cout << f[b - a] << endl;
    }
}