#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>

using namespace std;

int n, m;
int sx, sy, ex, ey;
char a[105][105]{};
bool v[105][105]{};
struct Coord {
    int x, y;
    bool operator<(const Coord& c) const {
        return x == c.x ? y < c.y : x < c.x;
    }
};
map<Coord, Coord> transfer;
struct Node {
    int x, y;
    int step;
};
int ans;

void bfs() {
    queue<Node> q;
    v[sx][sy] = true;
    q.push({sx, sy, 0});
    while (!q.empty()) {
        Node f{q.front()};
        q.pop();
        if (f.x == ex && f.y == ey) {
            ans = f.step;
            return;
        }
        int dx[]{0, 0, 1, -1};
        int dy[]{1, -1, 0, 0};
        for (int i{0}; i < 4; i++) {
            int nx{f.x + dx[i]}, ny{f.y + dy[i]};
            if (a[nx][ny] != '#' && !v[nx][ny]) {
                v[nx][ny] = true;
                q.push({nx, ny, f.step + 1});
            }
        }
        if (isalpha(a[f.x][f.y])) {
            Coord tr{transfer[{f.x, f.y}]};
            if (!v[tr.x][tr.y]) {
                v[tr.x][tr.y] = true;
                q.push({tr.x, tr.y, f.step + 1});
            }
        }
    }
}

int main() {
    int t;
    ios::sync_with_stdio(false);
    cin >> t;
    for (int css{1}; css <= t; css++) {
        cin >> n >> m;
        memset(a, '#', sizeof(a));
        memset(v, 0, sizeof(v));
        transfer = map<Coord, Coord>{};
        Coord tempA[30]{}, tempB[30]{};
        for (int i{1}; i <= n; i++) {
            for (int j{1}; j <= m; j++) {
                cin >> a[i][j];
                if (a[i][j] == 'B') {
                    sx = i, sy = j;
                    a[i][j] = '.';
                } else if (a[i][j] == 'I') {
                    ex = i, ey = j;
                    a[i][j] = '.';
                } else if (isalpha(a[i][j])) {
                    int num{a[i][j] - 'a'};
                    if (tempA[num].x != 0) {
                        tempB[num] = {i, j};
                    } else
                        tempA[num] = {i, j};
                }
            }
        }
        for (int i{0}; i < 26; i++) {
            if (tempA[i].x == 0)
                continue;
            transfer.insert({tempA[i], tempB[i]});
            transfer.insert({tempB[i], tempA[i]});
        }
        ans = -1;
        bfs();
        cout << "Case #" << css << ": " << ans << endl;
    }
}