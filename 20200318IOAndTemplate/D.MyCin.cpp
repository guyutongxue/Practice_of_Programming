#include <iostream>
using namespace std;
class MyCin {
    bool failbit = false;

public:
    MyCin& operator>>(int& content) {
        if (!failbit) {
            cin >> content;
            if (content == -1)
                failbit = true;
        }
        return *this;
    }
    operator bool() {
        return !failbit;
    }
};
int main() {
    MyCin m;
    int n1, n2;
    while (m >> n1 >> n2)
        cout << n1 << " " << n2 << endl;
    return 0;
}