#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    string str;
    while (cin >> str) {
        string result(str.length(), ' ');
        stack<int> parens;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '(') {
                parens.push(i);
            }
            if (str[i] == ')') {
                if (parens.empty()) {
                    result[i] = '?';
                } else {
                    parens.pop();
                }
            }
        }
        while (!parens.empty()) {
            result[parens.top()] = '$';
            parens.pop();
        }
        cout << str << endl;
        cout << result << endl;
    }
}