#include <algorithm>
#include <iostream>
using namespace std;

int ans{-1};
int workingDay[2]{};
int w[17]{};
int s[17]{};

void dfs(int spirit, int wealth, int day) {
    if (day > 15) {
        if (workingDay[0] <= workingDay[1]) {
            ans = max(ans, wealth);
        }
        return;
    }
    dfs(spirit, wealth, day + 1);
    if (spirit >= s[day]) {
        workingDay[day > 10]++;
        dfs(spirit - s[day], wealth + w[day], day + 1);
        workingDay[day > 10]--;
    }
}

int main() {
    int t;
    cin >> t;
    for (int i{1}; i <= 15; i++) {
        cin >> w[i] >> s[i];
    }
    dfs(t, 0,1);
    cout << ans << endl;
}