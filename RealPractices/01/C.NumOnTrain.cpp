#include <iostream>
using namespace std;
int x[20] = {};
int y[20] = {};
int main() {
    int a, n, m, t;
    cin >> a >> n >> m >> t;
    x[1] = 1;
    x[2] = 1;
    x[3] = 2;
    y[1] = 0;
    y[2] = 0;
    y[3] = 0;
    for (int i = 4; i <= n - 1; i++) {
        x[i] = x[i - 1] + x[i - 2] - 1;
        y[i] = y[i - 1] + y[i - 2] + 1;
        // cout << x[i] << " " << y[i] << endl;
    }
    int u = (m - x[n - 1] * a) / (y[n - 1] == 0 ? 1 : y[n - 1]);
    cout << x[t] * a + y[t] * u;
}