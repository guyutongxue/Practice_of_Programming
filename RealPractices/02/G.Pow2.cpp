#include <iostream>
#include <string>
using namespace std;
string parse(int n) {
    string result;
    bool isFirst = true;
    for (int i = 16; i >= 2; i--) {
        if (n & (1 << i)) {
            result += (isFirst ? "" : "+");
            result += "2(" + parse(i) + ")";
            isFirst = false;
        }
    }
    if (n & 2) {
        result += (isFirst ? "2" : "+2");
        isFirst = false;
    }
    if (n & 1) {
        result += (isFirst ? "2(0)" : "+2(0)");
        isFirst = false;
    }
    return result;
}
int main() {
    int n;
    cin >> n;
    cout << parse(n) << endl;
}