
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;
class CMean {
public:
    int* n;
    int i = 0;
    int tmp = 0;
    CMean(int& x) {
        n = &x;
    }
    void operator()(int x) {
        tmp += x;
        i++;
        *n = tmp / i;
    }
};

int main(int argc, char* argv[]) {
    int v;
    int t;
    cin >> t;
    while (t--) {
        cin >> v;
        vector<int> vec;
        while (v) {
            vec.push_back(v);
            cin >> v;
        }
        int myAver = 0;
        for_each(vec.begin(), vec.end(), CMean(myAver));
        cout << myAver << endl;
    }
    return 0;
}