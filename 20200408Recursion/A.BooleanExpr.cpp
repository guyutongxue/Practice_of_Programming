// Copied from Introduction_to_Computing/P3-3/7

#include <iostream>
#include <sstream>
#include <stack>
using namespace std;
stringstream ss;
bool parse() {
    char c;
    bool isNot = false;
    stack<bool> b;
    stack<char> s;
    while (ss >> c, !ss.eof()) {
        if (c == ' ')
            continue;
        if (c == ')')
            return b.top();
        if (c == '!')
            isNot ^= true;
        if (c == 'V')
            b.push(isNot ^ true), isNot = false;
        if (c == 'F')
            b.push(isNot ^ false), isNot = false;
        if (c == '&' || c == '|')
            s.push(c);
        if (c == '(')
            b.push(isNot ^ parse()), isNot = false;
        if (b.size() == 2) {
            bool a1 = b.top();
            b.pop();
            bool a2 = b.top();
            b.pop();
            b.push(s.top() == '&' ? a1 && a2 : a1 || a2);
            s.pop();
        }
    }
    return b.top();
}
int main() {
    string a;
    int num = 0;
    while (getline(cin, a)) {
        ss << a;
        cout << "Expression " << ++num << ": " << (parse() ? 'V' : 'F') << endl;
        ss.clear();
    }
    return 0;
}