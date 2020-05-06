#include <algorithm>
#include <cmath>
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
class MyFunc {
public:
    int p;
    MyFunc(int p) : p(p) {}
    int operator()(int x) {
        int res = 1;
        while (p--) {
            res *= x;
        }
        return res;
    }
};
int main() {
    int n;
    cin >> n;
    while (n--) {
        vector<MyFunc> v;
        for (int i = 0; i < 5; ++i)
            v.push_back(MyFunc(i + 1));
        int ans = 1;
        for (int i = 0; i < 5; ++i) {
            int m;
            cin >> m;
            ans += v[i](m);
        }
        cout << ans << endl;
    }
}