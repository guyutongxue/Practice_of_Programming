#include <cmath>
#include <iostream>
using namespace std;
int gcd(int x,int y){
    int r = x % y;
    while(r != 0){
        x = y;
        y = r;
        r = x % y;
    }
    return y;
}
int main() {
    int n, a, b;
    cin >> n >> a >> b;
    int g = gcd(a,b);
    a /= g;
    b /= g;
    double eps = 2;
    int ansi = 0, ansj = 0;
    for (int i = 1; i <= n; i++) {
        if (i % b == 0)
            continue;
        for (int j = 1; j <= i; j++) {
            double d = 1. * a / b - 1. * j / i;
            if (d < 0)
                break;
            if (d < eps) {
                eps = d;
                ansi = i;
                ansj = j;
            }
        }
    }
    cout << ansj << " " << ansi;
}