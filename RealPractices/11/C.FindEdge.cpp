// DFS

#include <math.h>
#include <memory.h>
#include <stdlib.h>

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

int map[505][505];
int r, c;
int dir1[4] = {0, 0, 1, -1}, dir2[4] = {1, -1, 0, 0};
int kept[505][505];

void dfs(int x, int y) {
    kept[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int xx = x + dir1[i], yy = y + dir2[i];
        if (kept[xx][yy] != 1 && map[xx][yy] == 1)
            dfs(xx, yy);
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        memset(kept, 0, sizeof(int) * 505 * 505);
        memset(map, 0, sizeof(int) * 505 * 505);
        scanf("%d%d", &r, &c);
        char ch;
        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++) {
                cin >> ch;
                if (ch == 'O')
                    map[i][j] = 1;
                else
                    map[i][j] = 2;
            }
        for (int i = 1; i <= r; i++) {
            if (map[i][1] == 1 && kept[i][1] == 0)
                dfs(i, 1);
            if (map[i][c] == 1 && kept[i][c] == 0)
                dfs(i, c);
        }
        for (int i = 1; i <= c; i++) {
            if (map[1][i] == 1 && kept[1][i] == 0)
                dfs(1, i);
            if (map[r][i] == 1 && kept[r][i] == 0)
                dfs(r, i);
        }
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                if (map[i][j] == 2)
                    printf("X");
                else if (kept[i][j])
                    printf("O");
                else
                    printf("X");
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}