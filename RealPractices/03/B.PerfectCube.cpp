#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    for (int i = 6; i <= n; i++) {
        for (int j = 2; j <= n; j++) {
            for (int k = j; k <= n; k++) {
                for (int l = k; l <= n; l++) {
                    if (i * i * i == j * j * j + k * k * k + l * l * l) {
                        cout << "Cube = " << i << ", Triple = (" << j << ',' << k << ',' << l << ')'
                             << endl;
                    }
                }
            }
        }
    }
}