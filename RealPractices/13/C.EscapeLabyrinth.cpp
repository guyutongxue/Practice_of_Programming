#include <cstring>
#include <iostream>
#include <limits>
#include <queue>
using namespace std;

struct Node {
    int x, y;
    int t;
};

int m, t;
char map[12][12]{};
int sx, sy, ex, ey;
int bfs() {
    if (sx == ex && sy == ey) {
        return 0;
    }
    int dx[]{0, 0, 1, -1};
    int dy[]{1, -1, 0, 0};
    queue<Node> q;
    q.push({sx, sy, 0});
    while (!q.empty()) {
        Node t{q.front()};
        q.pop();
        if (t.x == ex && t.y == ey) {
            return t.t;
        }
        for (int i{0}; i < 4; i++) {
            int nx{t.x + dx[i]};
            int ny{t.y + dy[i]};
            if (map[nx][ny] == '.') {
                q.push({nx, ny, t.t + 1});
                map[nx][ny] = '#';
            }
        }
    }
    return numeric_limits<int>::max();
}

int main() {
    int k;
    cin >> k;
    while (k--) {
        cin >> m >> t;
        memset(map, '#', sizeof(map));
        for (int i{1}; i <= m; i++) {
            for (int j{1}; j <= m; j++) {
                cin >> map[i][j];
                if (map[i][j] == 'S') {
                    sx = i;
                    sy = j;
                    map[i][j] = '.';
                } else if (map[i][j] == 'E') {
                    ex = i;
                    ey = j;
                    map[i][j] = '.';
                }
            }
        }
        cout << (bfs() <= t ? "YES" : "NO") << endl;
    }
}