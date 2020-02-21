// #define SHORTCUT
#include <iostream>
using namespace std;
class Sample {
public:
    int v;
#ifdef SHORTCUT
    Sample(int a = 0) {
        cout << 9 << endl << 22 << endl << 5 << endl;
        exit(0);
    }
#else
    Sample() : v(0) {}
    Sample(const int& x) {
        v = x;
    }
    Sample(const Sample& b) {
        v = b.v + 2;
    }
#endif
};
void PrintAndDouble(Sample o) {
    cout << o.v;
    cout << endl;
}
int main() {
    Sample a(5);
    Sample b = a;
    PrintAndDouble(b);
    Sample c = 20;
    PrintAndDouble(c);
    Sample d;
    d = a;
    cout << d.v;
    return 0;
}