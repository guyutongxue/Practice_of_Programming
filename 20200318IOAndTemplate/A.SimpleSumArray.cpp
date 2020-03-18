#include <iostream>
#include <string>
using namespace std;
template <class T>
T SumArray(const T* begin, const T* end) {
    T s;
    for (const T* i = begin; i != end; ++i)
        s += *i;
    return s;
}
int main() {
    string array[4] = {"Tom", "Jack", "Mary", "John"};
    cout << SumArray(array, array + 4) << endl;
    int a[4] = {1, 2, 3, 4};  //提示：1+2+3+4 = 10
    cout << SumArray(a, a + 4) << endl;
    return 0;
}