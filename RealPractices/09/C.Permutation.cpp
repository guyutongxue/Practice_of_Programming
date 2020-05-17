#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
char str[7];
int main() {
    cin >> str;
    int len = strlen(str);
    do {
        cout << str << endl;
    } while (next_permutation(str, str + len));
}