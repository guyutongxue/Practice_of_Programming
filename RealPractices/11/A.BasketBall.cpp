#include <algorithm>
#include <iostream>
using namespace std;

char a[1002][1002]{};
int ans{};

void dfs(int x, int y) {
    if (x == 5) {
        int score[5]{};
        for (int i = 1; i <= 4; i++) {
            for (int j = i + 1; j <= 4; j++) {
                if (a[i][j] == 'L')
                    score[j]++;
                if (a[i][j] == 'W')
                    score[i]++;
            }
        }
        int sum{0};
        for (int i = 2; i <= 4; i++)
            sum += (score[i] > score[1]);
        ans = min(ans, sum + 1);
        return;
    }
    if (x != y && a[x][y] == '?') {
        a[x][y] = 'L';
        y == 4 ? dfs(x + 1, x + 1) : dfs(x, y + 1);
        a[x][y] = 'W';
        y == 4 ? dfs(x + 1, x + 1) : dfs(x, y + 1);
        a[x][y] = '?';
    } else {
        y == 4 ? dfs(x + 1, x + 1) : dfs(x, y + 1);
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        for (int i = 1; i <= 4; i++) {
            cin >> (a[i] + 1);
        }
        ans = 5;
        dfs(1, 1);
        cout << ans << endl;
    }
}
