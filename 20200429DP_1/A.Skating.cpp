// POJ 1088
// Luogu P1434

#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

int r, c;
int mem[102][102];
int a[102][102] = {};
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, -1, 1};

/**
 * @brief 返回从某点出发的最长滑行长度。
 * 若为 1，表示无处可滑（极小值点）。
 * @param x 纵坐标
 * @param y 横坐标
 * @return int 最长的滑行长度
 */
int search(int x, int y) {
    auto isInside = [](int x, int y) { return x > 0 && x <= r && y > 0 && y <= c; };
    if (mem[x][y] != -1)
        return mem[x][y];
    int res = 1;
    for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if (isInside(nx, ny) && a[nx][ny] < a[x][y]) {
            res = max(res, search(nx, ny) + 1);
        }
    }
    mem[x][y] = res;
    return res;
}

int main() {
    memset(a, 0, sizeof(a));
    memset(mem, -1, sizeof(mem));
    cin >> r >> c;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            cin >> a[i][j];
        }
    }
    int ans = -1;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            ans = max(ans, search(i, j));
        }
    }
    cout << ans << endl;
}