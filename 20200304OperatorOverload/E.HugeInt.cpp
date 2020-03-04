#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
const int MAX = 110;
class CHugeInt {};
#include <sstream>
using namespace std;
class MyHugeInt {
private:
    string s;
    static string addString(string a, string b) {
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
    MyHugeInt(string s) : s(s) {}
    MyHugeInt(int n) {
        stringstream ss;
        ss << n;
        s = ss.str();
    }
    MyHugeInt operator+(const MyHugeInt& x) const {
        return MyHugeInt(addString(s, x.s));
    }
    MyHugeInt operator+(int x) const {
        stringstream ss;
        ss << x;
        return MyHugeInt(addString(s, ss.str()));
    }
    MyHugeInt& operator+=(int x) {
        stringstream ss;
        ss << x;
        s = addString(s, ss.str());
        return *this;
    }
    MyHugeInt& operator++() {
        operator+=(1);
        return *this;
    }
    MyHugeInt operator++(int) {
        MyHugeInt result(*this);
        operator++();
        return result;
    }
    friend MyHugeInt operator+(int, const MyHugeInt&);
    friend ostream& operator<<(ostream&, const MyHugeInt&);
};
MyHugeInt operator+(int x, MyHugeInt& y) {
    return y + x;
}
ostream& operator<<(ostream& o, const MyHugeInt& x) {
    o << x.s;
    return o;
}
#define CHugeInt MyHugeInt
int removeBrace[1] = {};
int main() {
    char s[210];
    int n;

    while (cin >> s >> n) {
        CHugeInt a(s);
        CHugeInt b(n);

        cout << a + b << endl;
        cout << n + a << endl;
        cout << a + n << endl;
        b += n;
        cout << ++b << endl;
        cout << b++ << endl;
        cout << b << endl;
    }
    return 0;
}