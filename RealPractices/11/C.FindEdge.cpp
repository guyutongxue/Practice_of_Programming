#include <cstring>
#include <iostream>
using namespace std;

char map[505][505];
int r, c;
int dx[4]{0, 0, 1, -1};
int dy[4]{1, -1, 0, 0};
void dfs(int x, int y) {
    map[x][y] = 'A';
    for (int i{0}; i < 4; i++) {
        int nx{x + dx[i]};
        int ny{y + dy[i]};
        if (nx >= 0 && nx < r && ny >= 0 && ny < c && map[nx][ny] == 'O')
            dfs(nx, ny);
    }
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> r >> c;
        for (int i{0}; i < r; i++) {
            for (int j{0}; j < c; j++) {
                cin >> map[i][j];
            }
        }
        for (int i{0}; i < r; i++) {
            if (map[i][0] == 'O')
                dfs(i, 0);
            if (map[i][c - 1] == 'O')
                dfs(i, c - 1);
        }
        for (int i{0}; i < c; i++) {
            if (map[0][i] == 'O')
                dfs(0, i);
            if (map[r - 1][i] == 'O')
                dfs(r - 1, i);
        }
        for (int i{0}; i < r; i++) {
            for (int j{0}; j < c; j++) {
                if (map[i][j] == 'A')
                    cout << 'O';
                else
                    cout << 'X';
            }
            cout << endl;
        }
        cout << endl;
    }
}