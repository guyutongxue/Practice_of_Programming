#include <iostream>
#include <map>
#include <string>
using namespace std;
string sub[5010];
map<string, int> m;
int main() {
    string str, t;
    int k = 0;
    cin >> str;
    for (int i = 1; i <= str.length(); i++) {
        for (int j = 0; j <= str.length() - i; j++) {
            t = str.substr(j, i);
            m[t]++;
        }
    }
    for (auto i : m)
        if (i.second > 1)
            cout << i.first << " " << i.second << endl;
    return 0;
}