#include <iostream>
using namespace std;
#include <complex>
class Complex : public complex<int> {
public:
    Complex() : complex(0) {}
    Complex(int a) : complex(a) {}
    Complex(const char* a) : complex(a[0] - '0', a[2] - '0') {}
};

ostream& operator<<(ostream& o, const complex<int>& c) {
    if(c.imag()==0)
        cout<<c.real();
    else if(c.real()==0)
        cout << c.imag() << 'i';
    else 
        o << c.real() << '+' << c.imag() << 'i';
    return o;
}

int main() {
    Complex c1;
    Complex c2("3+2i");  // 用字符串初始化时，只需考虑"a+bi"的形式，其中a和b都是1位数字
    Complex c3(c2);
    Complex c4(-15);
    cout << c2 << endl;
    cout << c3 << endl;
    cout << c4 << endl;
    cout << c2 + c4 << endl;
    cout << c2 - c3 << endl;
    cout << c2 * c3 << endl;
    c2 += c4;
    cout << c2 << endl;
    c2 -= -12;
    cout << c2 << endl;
    c3 *= c3;
    cout << c3 << endl;
    return 0;
}