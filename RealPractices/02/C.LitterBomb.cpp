#include <iostream>
using namespace std;

#include <cstring>
#include <iostream>
using namespace std;

// How many litters can be cleared in map[x][y]
int map[1025][1025] = {};

// Point which has litters.
struct Point {
    int x;
    int y;
    int v;
};

Point p[21];

int main() {
    memset(map, 0, sizeof(map));
    int d, n;
    cin >> d >> n;
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y >> p[i].v;
    }
    int ans = -1, num = 0;
    for (int i = 0; i < n; i++) {
        for (int row = p[i].x - d; row <= p[i].x + d; row++)
            if (row >= 0 && row < 1025) {
                for (int col = p[i].y - d; col <= p[i].y + d; col++) {
                    if (col >= 0 && col < 1025) {
                        map[row][col] += p[i].v;
                        if (ans < map[row][col]) {
                            ans = map[row][col];
                            num = 1;
                        } else if (ans == map[row][col])
                            num++;
                    }
                }
            }
    }
    cout << num << ' ' << ans;
    return 0;
}