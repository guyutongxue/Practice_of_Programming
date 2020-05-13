#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
using namespace std;
struct A {
    int x;
    A(int x): x(x) {}
    virtual const char* getName() const {
        return "A";
    }
    bool operator<(const A& b) {
        return x < b.x;
    }
};
struct B : A {
    B(int x): A(x) {}
    const char* getName() const override {
        return "B";
    }
};
void Print(const A* const a) {
    cout << a->getName() << ' ' << a->x << endl;
}
struct Comp {
    bool operator()(A* const a, A* const b) const {
        return *a < *b;
    }
};
int main() {
    int t;
    cin >> t;
    set<A*, Comp> ct;
    while (t--) {
        int n;
        cin >> n;
        ct.clear();
        for (int i = 0; i < n; ++i) {
            char c;
            int k;
            cin >> c >> k;

            if (c == 'A')
                ct.insert(new A(k));
            else
                ct.insert(new B(k));
        }
        for_each(ct.begin(), ct.end(), Print);
        cout << "****" << endl;
    }
}