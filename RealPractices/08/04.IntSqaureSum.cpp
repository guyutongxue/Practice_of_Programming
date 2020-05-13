#include <iostream>
using namespace std;
struct CType {
    int n;
    void setvalue(int x) {
        n = x;
    }
    int operator++(int) {
        return n;
    }
};
ostream& operator<<(ostream& o, const CType& c) {
    o << (c.n) * (c.n);
    return o;
}

int main(int argc, char* argv[]) {
    CType obj;
    int n;
    cin >> n;
    while (n) {
        obj.setvalue(n);
        cout << obj++ << " " << obj << endl;
        cin >> n;
    }
    return 0;
}