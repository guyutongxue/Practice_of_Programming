#include <iostream>
using namespace std;
struct A {
    int value;
    A(int t) : value(t) {}
    int get_value() {
        return value;
    }
    A operator+(A* const b) {
        return A(value + b->value);
    }
    A* operator->() {
        return this;
    }
};
struct B : A {
    using A::A;
};
struct C : A {
    using A::A;
};
int main() {
    int t;
    cin >> t;
    while (t--) {
        int aa, bb, cc;
        cin >> aa >> bb >> cc;
        A a(aa);
        B b(bb);
        C c(cc);
        A* x = &a;
        A* y = &b;
        A* z = &c;
        cout << (x->get_value() + y->get_value() + z->get_value()) << " ";
        cout << ((*x) + y + z)->get_value() << endl;
    }
    return 0;
}