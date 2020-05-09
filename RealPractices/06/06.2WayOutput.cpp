#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;
class C1 {
};
class C2 : public vector<int> {
public:
    C2(int size, vector<int> v) : vector<int>(v) {}
    vector<int>::iterator operator*() {
        return begin();
    }
    int& operator[](int index) {
        return at(size() - 1 - index);
    }
};
#define C1 C2
int r[1] = {};
int main() {
    vector<int> v;
    int p;
    int size;
    int k;
    cin >> k;
    while (k--) {
        cin >> size;
        v.clear();
        for (int i = 0; i < size; ++i) {
            cin >> p;
            v.push_back(p);
        }
        C1 o1 = C1(size, v);
        ostream_iterator<int> it(cout, "---");
        copy(*o1, (*o1) + size, it);
        cout << endl;
        for (int i = 0; i < size; ++i) {
            o1[i] *= 2;
            cout << o1[i] << "***";
        }
        cout << endl;
    }
}