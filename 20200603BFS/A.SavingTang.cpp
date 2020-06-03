// HDU 5025

#include <cstring>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
int n, m;
int sx, sy;  // start point
int ex, ey;  // end point
char matrix[102][102];
bool visit[102][102][12][32] = {};

int cnt;
using Coord = pair<int,int>;
Coord snake[10];
struct Node {
    int x, y;
    int step;
    int key;
    int s; // snakes
    Node() = default;
    Node(int x, int y, int step = 0, int key = 0, int s = 0)
        : x(x), y(y), step(step), key(key), s(s) {}
};
bool isOk(int key, int id) {
    return key + 1 == id;
}
int bfs() {
    queue<Node> q;
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    visit[sx][sy][0][0] = true;
    q.push(Node(sx, sy));
    while (!q.empty()) {
        Node nx = q.front();
        q.pop();
        int x = nx.x;
        int y = nx.y;
        int step = nx.step;
        int key = nx.key;
        int s = nx.s;
        if (x == ex && y == ey && isOk(key, m + 1))
            return step;
        if (matrix[x][y] == 'S') {
            int id = find(snake, snake + cnt, Coord(x,y)) - snake;
            if (!((s >> id) & 1)){
                q.push(Node(x, y, step + 1, key, s | (1 << id)));
                continue;
            }
        }
        for (int i = 0; i < 4; i++) {
            int newx = x + dx[i];
            int newy = y + dy[i];
            if (newx >= 1 && newx <= n && newy >= 1 && newy <= n) {
                if (matrix[newx][newy] >= '1' && matrix[newx][newy] <= '9') {
                    if (isOk(key, matrix[newx][newy] - '0')) {
                        int newstatus = key + 1;
                        if (!visit[newx][newy][newstatus][s]) {
                            visit[newx][newy][newstatus][s] = true;
                            q.push(Node(newx, newy, step + 1, newstatus, s));
                        }
                    } else {
                        if (!visit[newx][newy][key][s]) {
                            visit[newx][newy][key][s] = true;
                            q.push(Node(newx, newy, step + 1, key, s));
                        }
                    }
                } else if (matrix[newx][newy] != '#') {
                    if (!visit[newx][newy][key][s]) {
                        visit[newx][newy][key][s] = true;
                        q.push(Node(newx, newy, step + 1, key, s));
                    }
                }
            }
        }
    }
    return -1;
}
int main() {
    while (cin >> n >> m, n) {
        memset(visit, false, sizeof(visit));
        cnt = 0;
        for (int i = 1; i <= n; i++) {
            cin >> (matrix[i] + 1);
            for (int j = 1; j <= n; j++) {
                if (matrix[i][j] == 'K') {
                    sx = i;
                    sy = j;
                }
                if (matrix[i][j] == 'T') {
                    ex = i;
                    ey = j;
                }
                if (matrix[i][j] == 'S') {
                    snake[cnt++] = {i, j};
                }
            }
        }
        int res = bfs();
        if (res != -1)
            cout << res << endl;
        else
            cout << "impossible" << endl;
    }
    return 0;
}