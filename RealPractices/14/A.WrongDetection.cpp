#include <iostream>
using namespace std;
bool a[102][102]{};
int n{};
bool detect() {
    bool row[102]{};
    bool col[102]{};
    for (int i{1}; i <= n; i++) {
        for (int j{1}; j <= n; j++) {
            row[i] ^= a[i][j];
            col[j] ^= a[i][j];
        }
    }
    for (int i{1}; i <= n; i++) {
        if (row[i] || col[i])
            return false;
    }
    return true;
}

int main() {
    cin >> n;
    for (int i{1}; i <= n; i++) {
        for (int j{1}; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    if (detect()) {
        cout << "OK" << endl;
        return 0;
    }
    for (int i{1}; i <= n; i++) {
        for (int j{1}; j <= n; j++) {
            a[i][j] ^= true;
            if (detect()) {
                cout << i << ' '<< j << endl;
                return 0;
            }
            a[i][j] ^= true;
        }
    }
    cout << "Corrupt" << endl;
}