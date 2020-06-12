#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

int r, c, k;
bool visited[105][105][15]{};
char map[105][105]{};
int sx, sy, ex, ey;
int dx[4]{0, 0, 1, -1};
int dy[4]{1, -1, 0, 0};
int isOk{false};

struct Node {
    int x, y;
    int time;
    Node(int x, int y, int time = 0) : x{x}, y{y}, time{time} {}
};
queue<Node> q;

void bfs() {
    while (!q.empty()) {
        Node now{q.front()};
        q.pop();
        for (int i{0}; i < 4; i++) {
            int nx{now.x + dx[i]};
            int ny{now.y + dy[i]};
            if (nx == ex && ny == ey) {
                cout << now.time + 1 << endl;
                isOk = true;
                return;
            }
            Node newone{nx, ny, now.time + 1};
            int modtime{newone.time % k};
            if (map[nx][ny] == '.' && !visited[nx][ny][modtime] ||
                map[nx][ny] == '#' && !visited[nx][ny][modtime] && modtime == 0) {
                visited[nx][ny][modtime] = true;
                q.push(newone);
            }
        }
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        q = queue<Node>{};
        memset(visited, 0, sizeof(visited));
        memset(map, 0, sizeof(map));
        isOk = false;
        cin >> r >> c >> k;
        for (int i{1}; i <= r; i++)
            for (int j{1}; j <= c; j++) {
                cin >> map[i][j];
                if (map[i][j] == 'S') {
                    map[i][j] = '.';
                    sx = i;
                    sy = j;
                } else if (map[i][j] == 'E') {
                    map[i][j] = '.';
                    ex = i;
                    ey = j;
                }
            }
        visited[sx][sy][0] = true;
        q.push({sx, sy});
        bfs();
        if (!isOk)
            cout << "Oop!" << endl;
    }
}