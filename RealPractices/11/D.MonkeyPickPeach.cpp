#include <algorithm>
#include <iostream>
using namespace std;

int bee[105]{};
int peach[105]{};

int main() {
    int hon{};
    while (cin >> hon, hon != -1) {
        int n{0};
        for (;cin >> peach[n] >> bee[n], peach[n] != -1; n++)
            ;
        int ans{0};
        for (int i{0}; i < n; i++) {
            int current{hon}, res{0};
            for (int j{i}; j < n; j++) {
                current -= bee[j];
                if (current < 0)
                    break;
                res += peach[j];
            }
            ans = max(ans, res);
        }
        cout << ans << endl;
    }
}