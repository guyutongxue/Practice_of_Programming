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
        for (int i{s.length()}; i > 0; i--) {
            for (int j{0}; j <= s.length() - i; j++) {
                string sub(s.substr(j, i));
                int count{0};
                for (int k{0}; k < sub.length() / 2; k++) {
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