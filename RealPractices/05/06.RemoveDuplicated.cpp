#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;

int main() {
    int t;
    int a[100];
    cin >> t;
    while (t--) {
        for (int i = 0; i < 12; ++i)
            cin >> a[i];
        ostream_iterator<int> c(cout," ");
        set<int> b;
        for (int i = 0; i < 12; ++i) {
            b.insert(a[i]);
        }
        std::copy(b.begin(), b.end(), c);
        cout << endl;
    }
    return 0;
}