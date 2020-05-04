#include <iostream>
#include <set>
using namespace std;
class Rectangle {
public:
    int a, b;
    Rectangle(int a, int b) : a(a), b(b) {}
    bool operator<(const Rectangle& x) const {
        return a * b == x.a * x.b ? a + b > x.a + x.b : a * b > x.a * x.b;
    }
};
struct Comp {
    bool operator()(const Rectangle& y, const Rectangle& x) const {
        return y.a + y.b == x.a + x.b ? y.a * y.b < x.a * x.b : y.a + y.b < x.a + x.b;
    }
};
ostream& operator<<(ostream& o,const Rectangle& x) {
    o << x.a * x.b << ' ' << 2 * (x.a + x.b);
    return o;
}
int main() {
    multiset<Rectangle> m1;
    multiset<Rectangle, Comp> m2;
    int n, a, b;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        m1.insert(Rectangle(a, b));
        m2.insert(Rectangle(a, b));
    }
    for (multiset<Rectangle>::iterator it = m1.begin(); it != m1.end(); it++) {
        cout << *it << endl;
    }
    cout << endl;
    for (multiset<Rectangle>::iterator it = m2.begin(); it != m2.end(); it++) {
        cout << *it << endl;
    }
    return 0;
}