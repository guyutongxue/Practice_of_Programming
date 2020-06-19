#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

int b[10]{};
int a[10]{};
int n, x;
int cnt;

int main() {
    cin >> n >> x;
    cnt = 0;
    for (int i{0}; i < n; i++) {
        cin >> b[i];
        a[i] = i + 1;
    }
    do {
        int win{0}, lose{0};
        for (int i{0}; i < n; i++) {
            (a[i] >= b[i] + x ? win : lose)++;
        }
        if (win > lose) {
            for (int i{0}; i < n; i++) {
                cout << a[i] << " \n"[i == n - 1];
            }
        }
    } while (next_permutation(a, a + n));
}