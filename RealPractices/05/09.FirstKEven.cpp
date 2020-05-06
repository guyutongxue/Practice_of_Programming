#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;
class MyQueue {
    int k;
    multiset<int, greater<int>> q;

public:
    MyQueue(int k) : k(k) {}
    friend istream& operator>>(istream&, MyQueue&);
    friend ostream& operator<<(ostream&, MyQueue&);
};
istream& operator>>(istream& i, MyQueue& x) {
    int s;
    i >> s;
    if (s % 2 == 0)
        x.q.insert(s);
    return i;
}
ostream& operator<<(ostream& o, MyQueue& x) {
    bool isFirst = true;
    int num = 0;
    for (auto& i : x.q) {
        o << (isFirst ? "" : " ") << i;
        isFirst = false;
        if (++num == x.k)
            break;
    }
    return o;
}
int rb[1]{};
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        MyQueue q(k);
        for (int i = 0; i < n; ++i)
            cin >> q;
        cout << q;
        cout << endl;
    }
    return 0;
}