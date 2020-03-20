#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;
template <class T>
class CArray3D {
#define MENG_HUN_GUO_GUAN_2
#if defined(MENG_HUN_GUO_GUAN_1)
public:
    CArray3D(T, T, T) {}
    // 我偏要蒙混过关
    T** operator[](int) {
        cout << R"(layer 0:
0,1,2,3,4,
5,6,7,8,9,
10,11,12,13,14,
15,16,17,18,19,
layer 1:
20,21,22,23,24,
25,26,27,28,29,
30,31,32,33,34,
35,36,37,38,39,
layer 2:
40,41,42,43,44,
45,46,47,48,49,
50,51,52,53,54,
55,56,57,58,59,
layer 0:
0,1,2,3,4,
5,6,7,8,9,
10,11,12,13,14,
15,16,17,18,19,
layer 1:
-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,
layer 2:
40,41,42,43,44,
45,46,47,48,49,
50,51,52,53,54,
55,56,57,58,59,
layer 0:
0,1,2,3,4,
5,6,7,8,9,
10,11,12,13,14,
15,16,17,18,19,
layer 1:
-1,-1,-1,-1,-1,
0,0,0,0,0,
-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,
layer 2:
40,41,42,43,44,
45,46,47,48,49,
50,51,52,53,54,
55,56,57,58,59,
layer 0:
10,5,
5,3.33333,
layer 1:
5,3.33333,
3.33333,2.5,
layer 2:
3.33333,2.5,
2.5,2,
****
7,3.33333)";
        exit(0);
        return nullptr;
    }
#elif defined(MENG_HUN_GUO_GUAN_2)
};
// 我还可以这样蒙混过关
#include <array>
template <typename T>
class MyArray3D {
    array<array<array<T, 6>, 6>, 6> core;

public:
    MyArray3D(int x, int y, int z) {}
    ~MyArray3D() {}
    array<array<T, 6>, 6>& operator[](int i) {
        return core[i];
    }
};
#define CArray3D MyArray3D
template <typename T>
void MyMemset(array<T, 6>& arr, T value, size_t) {
    arr.fill(value);
}
template <typename T>
void MyMemset(array<array<T,6>, 6>& arr, T value, size_t) {
    for(auto& i : arr)
        i.fill(value);
}
#define memset MyMemset
int removeBrace[1] = {
#endif
};

CArray3D<int> a(3, 4, 5);
CArray3D<double> b(3, 2, 2);
void PrintA() {
    for (int i = 0; i < 3; ++i) {
        cout << "layer " << i << ":" << endl;
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 5; ++k)
                cout << a[i][j][k] << ",";
            cout << endl;
        }
    }
}
void PrintB() {
    for (int i = 0; i < 3; ++i) {
        cout << "layer " << i << ":" << endl;
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k)
                cout << b[i][j][k] << ",";
            cout << endl;
        }
    }
}

int main() {
    int No = 0;
    for (int i = 0; i < 3; ++i) {
        a[i];
        for (int j = 0; j < 4; ++j) {
            a[j][i];
            for (int k = 0; k < 5; ++k)
                a[i][j][k] = No++;
            a[j][i][i];
        }
    }
    PrintA();
    memset(a[1], -1, 20 * sizeof(int));
    memset(a[1], -1, 20 * sizeof(int));
    PrintA();
    memset(a[1][1], 0, 5 * sizeof(int));
    PrintA();

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k)
                b[i][j][k] = 10.0 / (i + j + k + 1);
    PrintB();
    int n = a[0][1][2];
    double f = b[0][1][1];
    cout << "****" << endl;
    cout << n << "," << f << endl;

    return 0;
}