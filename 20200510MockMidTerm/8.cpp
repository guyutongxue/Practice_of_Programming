#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        map<string, set<string>> computer;
        map<string, queue<string>> backpack;
        int n;
        cin >> n;
        while (n--) {
            char a;
            string b, c;
            cin >> a >> b >> c;
            if (a == 'C') {
                backpack[b].push(c);
                if (backpack[b].size() > 6) {
                    computer[b].insert(backpack[b].front());
                    backpack[b].pop();
                }
            } else {
                auto res = computer[b].find(c);
                if (res == computer[b].end()) {
                    cout << "Failed" << endl;
                } else {
                    cout << "Success" << endl;
                    c = *res;
                    backpack[b].push(c);
                    if (backpack[b].size() > 6) {
                        computer[b].insert(backpack[b].front());
                        backpack[b].pop();
                    }
                    computer[b].erase(res);
                }
            }
        }
    }
}