#include <iostream>
#include <map>
#include <string>
using namespace std;
multimap<int, int> q;
int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--) {
        string cmd;
        cin >> cmd;
        if (cmd.at(0) == 'S') {
            int x, y;
            cin >> x >> y;
            q.insert({y, x});
        } else {
            int z;
            cin >> z;
            int sum = 0;
            while (z) {
                if (q.empty()) {
                    sum += 40 * z;
                    z = 0;
                } else {
                    auto p = *q.begin();
                    if (z < p.second) {
                        sum += p.first * z;
                        q.begin()->second -= z;
                        z = 0;
                    } else {
                        sum += p.first * p.second;
                        z -= p.second;
                        q.erase(q.begin());
                    }
                }
            }
            cout << sum << endl;
        }
    }
}