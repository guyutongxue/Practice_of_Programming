#include <iostream>
using namespace std;
int books[202] = {};
int friends[202] = {};
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> friends[i];
        books[friends[i]]++;
    }
    for (int i = 0; i < n; ++i) {
        if (books[friends[i]] > 1)
            cout << books[friends[i]] - 1 << endl;
        else
            cout << "BeiJu" << endl;
    }
}