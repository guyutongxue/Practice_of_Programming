#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#include <functional>
function<bool(int)> Pred(int x) {
    return [x](int a) -> bool { return (a >> x) & 1; };
}
int main(int argc, char** argv) {
    int n, x;
    vector<int> intVec;
    cin >> n >> x;
    while (x) {
        intVec.push_back(x);
        cin >> x;
    }
    cout << count_if(intVec.begin(), intVec.end(), Pred(n)) << endl;
    return 0;
}