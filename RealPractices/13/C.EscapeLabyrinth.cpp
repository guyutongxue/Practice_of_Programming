#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int x, y;
    int t;

    Node() = default;
    Node(int xx, int yy, int tt) : x(xx), y(yy), t(tt) {}
};

int m, t;
char mat[12][12] = {};

int bfs(int x0, int y0, int x1, int y1) {
    if (x0 == x1 && y0 == y1) {
        return 0;
    }
    int x, y;
    queue<Node> q;
    q.push({x0, y0, 0});
    while (!q.empty()) {
        Node nd{q.front()};
        q.pop();
        int x{nd.x};
        int y{nd.y};
        if (x < m - 1) {
            if (mat[x + 1][y] == 'E') {
                return nd.t + 1;
            } else if (mat[x + 1][y] == '.') {
                q.push(Node(x + 1, y, nd.t + 1));
                mat[x + 1][y] = '*';
            }
        }
        if (x > 0) {
            if (mat[x - 1][y] == 'E') {
                return nd.t + 1;
            } else if (mat[x - 1][y] == '.') {
                q.push(Node(x - 1, y, nd.t + 1));
                mat[x - 1][y] = '*';
            }
        }
        if (y < m - 1) {
            if (mat[x][y + 1] == 'E') {
                return nd.t + 1;
            } else if (mat[x][y + 1] == '.') {
                q.push(Node(x, y + 1, nd.t + 1));
                mat[x][y + 1] = '*';
            }
        }
        if (y > 0) {
            if (mat[x][y - 1] == 'E') {
                return nd.t + 1;
            } else if (mat[x][y - 1] == '.') {
                q.push(Node(x, y - 1, nd.t + 1));
                mat[x][y - 1] = '*';
            }
        }
    }
    return -1;
}

int main() {
    int  k, x0, y0, x1, y1;
    cin >> k;
    while (k--) {
        cin >> m >> t;
        for (int i{0}; i < m; i++) {
            for (int j{0}; j < m; j++) {
                cin >> mat[i][j];
                if (mat[i][j] == 'S') {
                    x0 = i;
                    y0 = j;
                } else if (mat[i][j] == 'E') {
                    x1 = i;
                    y1 = j;
                }
            }
        }
        int ans{bfs(x0, y0, x1, y1)};
        if (ans <= t && ans >= 0) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}