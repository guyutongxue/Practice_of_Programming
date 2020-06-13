#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

bool visited[260][260][10];
char map[260][260];
int m, n, h;

struct State {
    int x, y;
    int life;
    int step;
};


int bfs() {
    visited[1][1][h] = true;
    queue<State> q;
    q.push({1, 1, h, 0});
    while (!q.empty()) {
        State c{q.front()};
        q.pop();
        if (c.x == m && c.y == n) {
            return c.step;
        }
        int dx[4]{0, 0, 1, -1};
        int dy[4]{1, -1, 0, 0};
        for (int i{0}; i < 4; i++) {
            int nx{c.x + dx[i]};
            int ny{c.y + dy[i]};
            if (map[nx][ny] != '#') {
                int nlife = c.life;
                if (map[nx][ny] == '*')
                    nlife--;
                if (!nlife || visited[nx][ny][nlife])
                    continue;
                visited[nx][ny][nlife] = true;
                q.push({nx, ny, nlife, c.step + 1});
            }
        }
    }
    return -1;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        memset(visited, false, sizeof(visited));
        memset(map, '#', sizeof(map));
        cin >> m >> n >> h;
        for (int i{1}; i <= m; i++) {
            for (int j{1}; j <= n; j++) {
                cin >> map[i][j];
            }
        }
        cout << bfs() << endl;
    }
}