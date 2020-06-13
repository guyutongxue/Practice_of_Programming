#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

char map[105][105]{};

void dfs(int x, int y) {
    map[x][y] = '*';
    for (int i{x - 1}; i <= x + 1; i++) {
        for (int j{y - 1}; j <= y + 1; j++) {
            if (map[i][j] == '@') {
                dfs(i, j);
            }
        }
    }
}

int main() {
    int n, m;
    while (cin >> n >> m, n) {
        memset(map, '*', sizeof(map));
        for (int i{1}; i <= n; i++) {
            for (int j{1}; j <= m; j++) {
                cin >> map[i][j];
            }
        }
        bool isClear{true};
        int cnt{0};
        while (true) {
            int sx, sy;
            isClear=true;
            for (int i{1}; i <= n && isClear; i++) {
                for (int j{1}; j <= m && isClear; j++) {
                    if (map[i][j] == '@') {
                        isClear = false;
                        sx = i;
                        sy = j;
                    }
                }
            }
            if (isClear)
                break;
            dfs(sx, sy);
            cnt++;
        }
        cout << cnt << endl;
    }
}