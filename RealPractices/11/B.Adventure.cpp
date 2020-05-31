// BFS

#include <math.h>
#include <stdlib.h>

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
using namespace std;

int m, n, k, ans;
int map[25][25];
int dir1[4] = {0, 0, 1, -1}, dir2[4] = {1, -1, 0, 0};

struct node {
    int x, y;
    bool visited[105];
    int kind;
    node(int _x, int _y) {
        x = _x, y = _y;
        kind = 0;
    }
};
queue<node> all;

void bfs() {
    while (!all.empty()) {
        node now = all.front();
        all.pop();
        for (int i = 0; i < 4; i++) {
            int xx = now.x + dir1[i], yy = now.y + dir2[i];
            if (map[xx][yy] < 1 || now.visited[map[xx][yy]] == 1)
                continue;
            node newone(now);
            newone.x = xx, newone.y = yy;
            newone.visited[map[xx][yy]] = 1;
            newone.kind++;
            ans = max(ans, newone.kind);
            all.push(newone);
        }
    }
}

int main() {
    scanf("%d%d%d", &m, &n, &k);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &map[i][j]);
    node origin(1, 1);
    origin.kind = 1;
    for (int i = 1; i <= k; i++)
        origin.visited[i] = false;
    origin.visited[map[1][1]] = 1;
    all.push(origin);
    bfs();
    printf("%d\n", ans);
    return 0;
}