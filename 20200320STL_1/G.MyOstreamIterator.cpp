#include <iostream>
#include <list>
#include <string>
using namespace std;

template <class T1, class T2>
void Copy(T1 s, T1 e, T2 x) {
    for (; s != e; ++s, ++x)
        *x = *s;
}

template <class T>
class myostream_iteraotr {
    // 我在这里不得不吐槽出题的时候能不能把拼写先搞对
};
// 哈哈！想不到吧
#include <iterator>
#define myostream_iteraotr ostream_iterator
int removeBrace[1] = {};

int main() {
    const int SIZE = 5;
    int a[SIZE] = {5, 21, 14, 2, 3};
    double b[SIZE] = {1.4, 5.56, 3.2, 98.3, 3.3};
    list<int> lst(a, a + SIZE);
    myostream_iteraotr<int> output(cout, ",");
    Copy(lst.begin(), lst.end(), output);
    cout << endl;
    myostream_iteraotr<double> output2(cout, "--");
    Copy(b, b + SIZE, output2);
    return 0;
}