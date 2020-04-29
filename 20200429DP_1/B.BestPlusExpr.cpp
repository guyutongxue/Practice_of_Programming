#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// code copied from 20200304/E
class MyHugeInt {
private:
    string s;
    static string addString(string a, string b) {
        if (a == "" || b == "")
            throw "wrong: " + a + ' ' + b;
        if (a.length() > b.length())
            b = string(a.length() - b.length(), '0') + b;
        else
            a = string(b.length() - a.length(), '0') + a;
        string result;
        auto p = a.end() - 1;
        auto q = b.end() - 1;
        bool step = false;
        while (p >= a.begin()) {
            int r = (*p) - '0' + (*q) - '0' + int(step);
            result = char(r % 10 + '0') + result;
            step = r >= 10;
            p--, q--;
        }
        if (step)
            result = '1' + result;
        return result;
    }

public:
    MyHugeInt() : s("") {}
    MyHugeInt(string s) : s(s) {}
    MyHugeInt(int n) {
        stringstream ss;
        ss << n;
        s = ss.str();
    }
    MyHugeInt operator+(const MyHugeInt& x) const {
        return MyHugeInt(addString(s, x.s));
    }
    // MyHugeInt operator+(int x) const {
    //     stringstream ss;
    //     ss << x;
    //     return MyHugeInt(addString(s, ss.str()));
    // }
    // MyHugeInt& operator+=(int x) {
    //     stringstream ss;
    //     ss << x;
    //     s = addString(s, ss.str());
    //     return *this;
    // }
    // MyHugeInt& operator++() {
    //     operator+=(1);
    //     return *this;
    // }
    // MyHugeInt operator++(int) {
    //     MyHugeInt result(*this);
    //     operator++();
    //     return result;
    // }
    bool operator<(const MyHugeInt& b) const {
        if (s == "")
            return false;
        if (b.s == "")
            return true;
        return s.length() == b.s.length() ? s < b.s : s.length() < b.s.length();
    }
    // friend MyHugeInt operator+(int, const MyHugeInt&);
    friend ostream& operator<<(ostream&, const MyHugeInt&);
};
// MyHugeInt operator+(int x, MyHugeInt& y) {
//     return y + x;
// }
ostream& operator<<(ostream& o, const MyHugeInt& x) {
    o << x.s;
    return o;
}

int main() {
    int m;
    string s;
    while (cin >> m >> s) {
        // dp[i][j] 指前 i 个数字中插入 j 个加号得到的最小值
        MyHugeInt dp[52][52];
        int len = s.length();
        for (int i = 0; i <= len; ++i) {
            dp[i][0] = s.substr(0, i);
        }
        for (int j = 1; j <= m; j++) {
            for (int i = 0; i <= len; ++i) {
                for (int k = j; k < i; k++) {
                    dp[i][j] = min(dp[i][j], dp[k][j - 1] + s.substr(k, i - k));
                }
            }
        }
        cout << dp[len][m] << endl;
    }
}