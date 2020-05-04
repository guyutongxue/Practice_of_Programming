#include <iostream>
using namespace std;

class A {
public:
};
#include <complex>
struct B : public complex<int> {
    using complex<int>::complex;
    B& getValue() {
        return *this;
    }
};
ostream& operator<<(ostream& o, complex<int> x) {
    o << x.real();
    return o;
}
#define A B
int hhhhh[1] = {};

int main() {
    int t;
    cin >> t;
    while (t--) {
        int m, n, k;
        cin >> m >> n >> k;
        A a(m);
        A b = a;
        cout << b << endl;
        cout << (a += b -= n) << endl;
        cout << a.getValue() << endl;
        a.getValue() = k;
        cout << a << endl;
    }
    return 0;
}