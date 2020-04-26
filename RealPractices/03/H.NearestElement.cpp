#include <algorithm>
#include <iostream>
using namespace std;

int a[100002];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int m;
    cin >> m;
    while (m--) {
        int v;
        cin >> v;
        int* pos = lower_bound(a, a + n, v);
        if (pos == a + n)
            pos--;
        else if (pos != a && *pos - v >= v - *(pos - 1))
            pos--;
        cout << *pos << endl;
    }
}