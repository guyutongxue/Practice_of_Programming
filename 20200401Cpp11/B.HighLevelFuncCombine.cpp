#include <iostream>
using namespace std;
#include <functional>
template <typename Func1, typename Func2, typename Value>
function<Value(Value)> combine(Func1 func1, Func2 func2) {
    return [=](Value value) -> Value { return func1(func1(value) + func2(value)); };
}
int main() {
    auto Square = [](double a) { return a * a; };
    auto Inc = [](double a) { return a + 1; };
    cout << combine<decltype(Square), decltype(Inc), int>(Square, Inc)(3) << endl;
    cout << combine<decltype(Inc), decltype(Square), double>(Inc, Square)(2.5) << endl;

    return 0;
}