#include <iostream>
using namespace std;

int main() {
    int64_t f[50];  // results
    int n, m;
    cin >> n >> m;
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        if (i < m)
            f[i] = 2 * f[i - 1];
        else if (i == m)
            f[i] = 2 * f[i - 1] - 1;
        else  // It's obvious that if we don't consider the condition of explosion, then we can
              // either put or not put in hole #i. That's the meaning of 2 * f[i - 1]. But If we put
              // one which just make an m-continious-consequence, then the explosion happen. We want
              // to remove this condition. If it construct an m-continious-consequence, hole #(i -
              // m), #(i - m + 1), ..., #i is full. So just consider hole #1 to #(i - m - 1), while
              // f[i - m + 1] just store how many conditions there. So minus it is the final answer.
            f[i] = 2 * f[i - 1] - f[i - m - 1];
    }
    cout << f[n] << endl;
    return 0;
}