#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
vector<int> numbers;
int main() {
    auto f = [](int d) { return [d](const int& p) -> bool { return p % d == 0; }; };
    int n, x, d;
    while (cin >> n) {
        numbers.clear();
        for (int i = 1; i <= n; i++) {
            cin >> x;
            numbers.push_back(x);
        }
        cin >> d;
        cout << count_if(numbers.begin(), numbers.end(), f(d)) << endl;
    }
    return 0;
}