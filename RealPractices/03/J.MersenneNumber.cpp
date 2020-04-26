#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;

int f[1001] = {};
int res[1001] = {};
int p;

template <int l>
void fast_power(int* dest, int* x, int* y) {
    int sav[2 * l + 1];
    memset(sav, 0, sizeof(sav));
    for (int i = 1; i <= l; i += 1)
        for (int j = 1; j <= l; j += 1)
            sav[i + j - 1] += x[i] * y[j];  // 先计算每一位的乘积
    for (int i = 1; i <= l; i += 1) {
        sav[i + 1] += sav[i] / 10;  // 单独处理进位
        sav[i] %= 10;
    }
    memcpy(dest, sav, sizeof(sav));
}
int main() {
    cin >> p;
    cout << (int)(log10(2) * p + 1) << endl;
    res[1] = 1;
    f[1] = 2;
    // 快速幂
    while (p != 0) {
        if (p % 2 == 1)
            fast_power<500>(res, res, f);
        p /= 2;
        fast_power<500>(f, f, f);
    }
    res[1] -= 1;
    for (int i = 500; i >= 1; i -= 1)
        // 50个换一行，第一个不用
        printf("\n%d" + !(i != 500 && i % 50 == 0), res[i]);
    return 0;
}