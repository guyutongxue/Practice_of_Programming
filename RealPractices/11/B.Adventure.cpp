// BFS

#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

int m, n, k, ans;
int map[25][25]{};

struct Node {
    int x, y;
    bool visited[105]{};
    int kind = 0;
    Node(int x, int y) : x{x}, y{y} {}
};
queue<Node> q;

void bfs() {
    int dx[4]{0, 0, 1, -1};
    int dy[4]{1, -1, 0, 0};
    while (!q.empty()) {
        Node now{q.front()};
        q.pop();
        for (int i = 0; i < 4; i++) {
            int newx = now.x + dx[i], newy = now.y + dy[i];
            if (map[newx][newy] < 1 || now.visited[map[newx][newy]])
                continue;
            Node curr{now};
            curr.x = newx, curr.y = newy;
            curr.visited[map[newx][newy]] = true;
            curr.kind++;
            ans = max(ans, curr.kind);
            q.push(curr);
        }
    }
}

int main() {
    cin >> m >> n >> k;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> map[i][j];
        }
    }
    Node root(1, 1);
    root.kind = 1;
    root.visited[map[1][1]] = true;
    q.push(root);
    bfs();
    cout << ans << endl;
    return 0;
}