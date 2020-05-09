#include <iostream>
using namespace std;
int gcd(int x, int y) {
    return x % y == 0 ? y : gcd(y, x % y);
}
class Fraction {
    int num, den;

public:
    Fraction(int num, int den = 1) : num(num), den(den) {}
    Fraction& operator*=(const Fraction& b) {
        *this = operator*(b);
        return *this;
    }
    Fraction& operator/=(const Fraction& b) {
        *this = operator/(b);
        return *this;
    }
    Fraction operator*(const Fraction& b) const {
        Fraction r(num * b.num, den * b.den);
        int&& x = gcd(r.num, r.den);
        r.num /= x;
        r.den /= x;
        return r;
    }
    Fraction operator/(const Fraction& b) const {
        return operator*(Fraction(b.den, b.num));
    }
    operator float() {
        return 1.f * num / den;
    }
    friend ostream& operator<<(ostream&, const Fraction&);
};
ostream& operator<<(ostream& o, const Fraction& f) {
    o << f.num << '/' << f.den;
    return o;
}
int r[1]={};

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    Fraction f(a, b), g(c);
    f *= g;
    cout << f << endl;
    f /= g;
    cout << f << endl;
    f = f * f;
    cout << f << endl;
    f = f / g;
    cout << f << endl;
    cout << (float)f << endl;
    return 0;
}