// POJ 1185

// Not finished yet


#include <algorithm>
#include <iostream>
using namespace std;

int n, m, sup;
int map[105] = {};
int f[105][105][105] = {};
int num[105] = {};
int state[105] = {};

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            (map[i] <<= 1) += (c == 'P');
        }
    }

    // This part check whether a `row` is available
    for (int i = 0; i < (1 << m); i++) {
        int cnt = 0;   // How many cannons put in this `row`
        int temp = i;  // The other (left) part of current `row`
        int flag = 0;  // Is it in other's territory?
        for (; temp > 0; temp >>= 1) {
            if (temp & 1) {    // If we plan to put a cannon here
                if (flag > 0)  // If this position is in other's territory
                    break;     // Then give up this `row`
                flag = 2;      // Now put a cannon here. Refresh the flag
                cnt++;
            } else
                flag--;  // Refresh flag
        }
        if (temp == 0) {                 // Only when all cannons planned is OK
            if ((map[1] | i) == map[1])  // Deal with the first line:
                f[1][sup][0] = cnt;      // If all the cannons are put in Plain, then store it; else
                                         // keep f[1][*][0] as 0
            num[sup] = cnt;              // Update necessary datas
            state[sup++] = i;
        }
    }
    for (int i = 2; i <= n; i++) {              // Current row we are dealing with
        for (int k1 = 0; k1 < sup; k1++) {      // Last row
            for (int k2 = 0; k2 < sup; k2++) {  // Last row of last row
                if (f[i - 1][k1][k2] == 0)  // If available solution between k1 & k2 doesn't exist
                    continue;               // Then ignore it
                for (int j = 0; j < sup; j++) {  // Check is this `row` is compatitable with k1 & k2
                    if ((state[k1] & state[j]) == 0 && (state[k2] & state[j]) == 0 &&
                        (map[i] | state[j]) == map[i]) {
                        f[i][j][k1] = max(f[i][j][k1], f[i - 1][k1][k2] + num[j]);
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < sup; i++) {
        for (int j = 0; j < sup; j++) {
            ans = max(ans, f[n][i][j]);
        }
    }

    cout << ans << endl;
}