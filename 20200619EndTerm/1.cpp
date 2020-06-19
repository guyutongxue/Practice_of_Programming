#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>

using namespace std;

using Coord = pair<int, int>;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        Coord a[52];
        // set<Coord> used;
        for (int i{1}; i <= n; i++) {
            cin >> a[i].first >> a[i].second;
            // if (used.find(a[i]) != used.end()) {
            //     i--, n--;
            //     continue;
            // }
            // used.insert(a[i]);
        }
        sort(a + 1, a + n + 1);
        n = (unique(a + 1, a + n + 1) - (a + 1));
        // {
        //     for (int i{1}; i <= n; i++) {
        //         cout << a[i].first <<"," << a[i].second <<endl;
        //     }
        // }
        int cnt{0};
        for (int i{1}; i <= n; i++) {
            for (int j{i + 1}; j <= n; j++) {
                if (a[i].first != a[j].first)
                    continue;
                for (int k{j + 1}; k <= n; k++) {
                    if (a[k].second != a[i].second)
                        continue;
                    for (int l{k + 1}; l <= n; l++) {
                        if (a[l].first == a[k].first && a[l].second == a[j].second) {
                            cnt++;
                        }
                    }
                }
            }
        }
        cout << cnt << endl;
    }
}