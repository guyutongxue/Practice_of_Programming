#include <iostream>
using namespace std;
class Apple {
public:
    static int nTotalNumber;
    Apple() {
        nTotalNumber++;
    }
    ~Apple() {
        nTotalNumber--;
    }
    static void PrintTotal() {
        cout << nTotalNumber << endl;
    }
};
int Apple::nTotalNumber = 0;
Apple Fun(const Apple& a) {
    a.PrintTotal();
    return a;
}
int main() {
    Apple* p = new Apple[4];
    Fun(p[2]); // Here, constructor not called (because it's copy init), but destructor called
    Apple p1, p2;
    Apple::PrintTotal();
    delete[] p;
    p1.PrintTotal();
    return 0;
}