#include <cstring>
#include <iostream>
using namespace std;

class Array2 {
private:
    int* p;
    int x, y;

public:
    Array2() : p(nullptr), x(0), y(0) {}
    Array2(int x, int y) : x(x), y(y) {
        p = new int[x * y];
    }
    Array2(const Array2& s) : x(s.x), y(s.y) {
        if (p)
            delete[] p;
        p = new int[x * y];
        memcpy(p, s.p, sizeof(int) * x * y);
    }
    Array2& operator=(const Array2& s) {
        if (p == s.p)
            return *this;
        x = s.x;
        y = s.y;
        if (p)
            delete[] p;
        p = new int[x * y];
        memcpy(p, s.p, sizeof(int) * x * y);
        return *this;
    }
    int* operator[](int i) {
        if (p)
            return p + y * i;
        else
            return nullptr;
    }
    int& operator()(int i, int j) {
        if (p)
            return *(p + y * i + j);
        else
            throw "What are you doing??";
    }
    ~Array2() {
        if (p)
            delete[] p;
    }
};

int main() {
    Array2 a(3, 4);
    int i, j;
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 4; j++)
            a[i][j] = i * 4 + j;
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 4; j++) {
            cout << a(i, j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;
    b = a;
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 4; j++) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}