#include <algorithm>
#include <iostream>

using namespace std;

int a[5][5];

int main() {
    for (int i{0}; i < 5; i++) {
        for (int j{0}; j < 5; j++) {
            cin >> a[i][j];
        }
    }
    for (int j{0}; j < 5; j++) {
        int minimum{numeric_limits<int>::max()};
        int pt{6};
        for (int i{0}; i < 5; i++) {
            if (a[i][j] < minimum) {
                minimum = a[i][j];
                pt = i;
            }
        }
        if (minimum == *std::max_element<int*>(*(a + pt), *(a + pt) + 5)) {
            cout << pt + 1 << " " << j + 1 << " " << minimum;
            return 0;
        }
    }
    cout << "not found" << endl;
}