// Longest Palindrom Substring

#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        if (s.length() <= 1) {
            cout << s << endl;
            continue;
        }
        for (int i = s.length(); i > 0; i--) {  //子串长度
            for (int j = 0; j <= s.length() - i; j++) {
                string sub = s.substr(j, i);                  //子串位置
                int count = 0;                                //计数，用来判断是否对称
                for (int k = 0; k < sub.length() / 2; k++) {  //左右对称判断
                    if (sub.at(k) == sub.at(sub.length() - k - 1))
                        count++;
                }
                if (count == sub.length() / 2) {
                    cout << sub << endl;
                    goto next;
                }
            }
        }
    next:;
    }
}