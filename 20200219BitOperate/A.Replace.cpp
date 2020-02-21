#include <iostream>
using namespace std;

// Debug Functions

// print in binary
inline void print(int x) {
    for (int i = 31; i >= 0; i--)
        cout << bool(x & (1 << i));
    cout << endl;
}
// get in binary
inline void get(int& x) {
    char c;
    x = 0;
    while (c = cin.get(), c != '\n') {
        (x <<= 1) += (c - '0');
    }
}
template <typename... Args>
void get(int& x, Args... args) {
    get(x);
    get(args...);
}
template <typename... Args>
void print(int x, Args... args) {
    print(x);
    print(args...);
}

// End of Debug Functions

int bitManipulation1(int n, int m, int i) {
    // print(n & (~(1 << i)),(m & (1 << i)));
    return (n & (~(1 << i))) | (m & (1 << i));
}

int main() {
    int n, m, i, t;
    cin >> t;
    // cin.ignore();
    while (t--) {
        cin >> n >> m >> i;
        // get(n, m);
        // cin >> i;
        // cin.ignore();
        // print(bitManipulation1(n, m, i));
        cout << bitManipulation1(n, m, i) << endl;
    }
    return 0;
}