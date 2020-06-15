#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;

int image[55][55]{};
bool visited[55][55]{};
unsigned h, w, m;

void dfs(int x, int y) {
    visited[x][y] = true;
    int dx[4]{0, 0, 1, -1};
    int dy[4]{1, -1, 0, 0};
    for (int i{0}; i < 4; i++) {
        int nx{x + dx[i]};
        int ny{y + dy[i]};
        if (!visited[nx][ny] && abs(image[x][y] - image[nx][ny]) <= m) {
            dfs(nx, ny);
        }
    }
}

int main() {
    while (cin >> h >> w >> m, h) {
        memset(image, 0x7f, sizeof(image));
        memset(visited, 0, sizeof(visited));
        for (int i{1}; i <= h; i++) {
            for (int j{1}; j <= w; j++) {
                cin >> image[i][j];
            }
        }
        bool isOk{false};
        int cnt{0};
        while (!isOk) {
            isOk = true;
            for (int i{1}; i <= h; i++) {
                for (int j{1}; j <= w; j++) {
                    if (!visited[i][j]) {
                        isOk = false;
                        cnt++;
                        dfs(i, j);
                    }
                }
            }
        }
        cout << cnt << endl;
    }
}