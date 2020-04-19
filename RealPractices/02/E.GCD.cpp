#include <iostream>
#if __cplusplus >= 201703L
#include <numeric>
int gcd(int a, int b) {
    // 有现成的就不要造轮子
    return std::gcd(a, b);
}
#else
#include <algorithm>
int gcd(int a, int b) {
    if (a < b)
        std::swap(a, b);
    int r = a % b;
    while (r != 0) {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}
#endif

int main() {
    int x, y;
    std::cin >> x >> y;
    std::cout << gcd(x, y) << std::endl;
}