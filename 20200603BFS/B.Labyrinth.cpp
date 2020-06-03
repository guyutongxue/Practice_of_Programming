#include <iostream>
#include <queue>
#include <vector>
using namespace std;

bool a[7][7] = {{1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 1},
                {1, 1, 1, 1, 1, 1, 1}

};

struct Coord {
    int x, y;
    Coord(int x, int y) : x(x), y(y) {
        path.push_back({x, y});
    }
    Coord(const Coord& o, int x, int y) : x(x), y(y) {
        path = o.path;
        path.push_back({x, y});
    }
    vector<pair<int, int>> path;
};

// BFS, not DFS
queue<Coord> q;

int main() {
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            cin >> a[i][j];
        }
    }
    Coord root(1, 1);
    q.push(root);
    while (!q.empty()) {
        Coord top = q.front();
        q.pop();
        if (top.x == 5 && top.y == 5) {
            for (auto i : top.path) {
                cout << "(" << i.first - 1 << ", " << i.second - 1 << ")" << endl;
            }
            return 0;
        }
        if (!a[top.x][top.y - 1])
            q.push(Coord(top, top.x, top.y - 1));
        if (!a[top.x][top.y + 1])
            q.push(Coord(top, top.x, top.y + 1));
        if (!a[top.x - 1][top.y])
            q.push(Coord(top, top.x - 1, top.y));
        if (!a[top.x + 1][top.y])
            q.push(Coord(top, top.x + 1, top.y));
    }
}