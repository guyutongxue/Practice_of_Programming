#include <cstring>
#include <iostream>
using namespace std;
template <int bitNum>
struct MyBitset {
    char a[bitNum / 8 + 1];
    MyBitset() {
        memset(a, 0, sizeof(a));
    };
    void Set(int i, int v) {
        char& c = a[i / 8];
        int bp = i % 8;
        if (v)
            c |= (1 << bp);
        else
            c &= ~(1 << bp);
    }
// 蒙混过关小王子
};
#include <bitset>
#include <sstream>
#include <algorithm>
stringstream ss;
string s;
#define MyBitset bitset
#define Set set
#define Print() size(),\
ss.clear(),\
ss << bs,\
ss >> s,\
reverse(s.begin(),s.end()),\
cout << s << endl
struct F {
    int bitNum;
    bool operator[](int){//\
    void Print() {
        for (int i = 0; i < bitNum; ++i)
            cout << (*this)[i];
        cout << endl;
    }
};

int main() {
    int n;
    int i, j, k, v;
    while (cin >> n) {
        MyBitset<20> bs;
        for (int i = 0; i < n; ++i) {
            int t;
            cin >> t;
            bs.Set(t, 1);
        }
        bs.Print();
        cin >> i >> j >> k >> v;
        bs[k] = v;
        bs[i] = bs[j] = bs[k];
        bs.Print();
        cin >> i >> j >> k >> v;
        bs[k] = v;
        (bs[i] = bs[j]) = bs[k];
        bs.Print();
    }
    return 0;
}