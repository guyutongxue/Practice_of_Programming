#include <iostream>
using namespace std;
int main() {
    int p, e, i, d;
    cin >> p >> e >> i >> d;
    int o = d;
    while ((d - p) % 23) {
        d++;
    }
    while ((d - e) % 28) {
        d += 23;
    }
    while ((d - i) % 33) {
        d += 23 * 28;
    }
    cout << (d - o == 0 ? 21252 : d - o);
}