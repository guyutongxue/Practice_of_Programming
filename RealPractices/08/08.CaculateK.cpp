#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, i, j;
        cin >> n >> i >> j;
        int sepi = (1 << i);
        int sepj = (1 << j);
        int k = 0;
        k |= (n & sepi);
        k |= ((n & sepj) ^ sepj);
        k |= (sepj - 2 *sepi); 
        cout << hex << k << endl;
    }
}