#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
using namespace std;
#include <sstream>
template <typename T>
struct Print {
    int index;
    int len;
    string res;
    Print(int len) : len(len), index(0), res("") {}
    Print operator+(const T& a) {
        stringstream ss;
        ss << res << a;
        index++;
        if (index == len) {
            cout << ss.str() << endl;
        }
        res = ss.str();
        return *this;
    }
};
int main() {
    string s[20];
    int num[20];
    int m, n;

    while (cin >> m >> n) {
        for (int i = 0; i < m; i++) {
            cin >> s[i];
        }
        accumulate(s, s + m, Print<string>(m));
        for (int i = 0; i < n; i++) {
            cin >> num[i];
        }
        accumulate(num, num + n, Print<int>(n));
    }
}