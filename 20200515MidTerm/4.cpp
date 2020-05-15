#include <iostream>
using namespace std;
int gcd(int a, int b) {  // 计算两个数的最大公约数
    return (!b) ? a : gcd(b, a % b);
}
class Fraction {
    int p, q;

public:
    Fraction(int p = 0, int q = 1) : p(p), q(q) {}
    friend istream& operator>>(istream&, Fraction&);
    friend ostream& operator<<(ostream&, const Fraction&);
    Fraction operator*(const Fraction& b) {
        return Fraction(p * b.p, q * b.q);
    }
};
istream& operator>>(istream& in, Fraction& f) {
    in >> f.p >> f.q;
    return in;
}
ostream& operator<<(ostream& out, const Fraction& f) {
    int&& t = gcd(f.p, f.q);
    int p = f.p / t, q = f.q / t;
    if (q == 1)
        out << p;
    else
        out << p << '/' << q;
    return out;
}
int a[1] = {};

int main() {
    int testcases;
    cin >> testcases;
    while (testcases--) {
        Fraction a, b, two(2);
        cin >> a >> b;
        cout << a << " * " << b << " = " << a * b << endl;
        cout << "2 * " << a << " = " << two * a << endl;
        cout << b << " * 3 = " << b * 3 << endl;
    }
    return 0;
}