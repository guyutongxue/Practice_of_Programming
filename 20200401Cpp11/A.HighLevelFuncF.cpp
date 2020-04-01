#include <iostream>
using namespace std;
#include <functional>
template <typename T, typename U>
function<U(U)> f(T t) {
    return [t](U u) -> U { return u + t; };
}
int main() {
    cout << f<int, int>(7)(9) << endl;                      // 16
    cout << f<string, string>(" hello!")("world") << endl;  // world hello!
    cout << f<char, string>('!')("world") << endl;

    return 0;  // world!
}