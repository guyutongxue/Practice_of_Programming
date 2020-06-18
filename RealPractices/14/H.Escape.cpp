#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#define MAKE_STATE(goalkey, x, y) (((goalkey << 16) | (x << 8)) | y)
#define GOALKEY(k) (k >> 16)
#define PX(k) ((k >> 8) & 0x000000ff)
#define PY(k) (k & 0x000000ff)
using namespace std;

int Keycnt;
int m, n;
int S[10020];  //密文牌号
int M[110][110];
int vis[110][110];  //解的密文数，小则舍弃

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
struct Node {
    int state;
    int step;
    Node(int state_, int step_) : state(state_), step(step_) {}
};

int main() {
    int T;
    cin >> T;
    while (T--) {
        scanf("%d%d", &m, &n);
        Keycnt = 0;
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= n; ++j) {
                cin >> M[i][j];
                if (M[i][j] > 1)
                    S[Keycnt++] = M[i][j];
            }
        memset(vis, 0xff, sizeof(vis));
        sort(S, S + Keycnt);
        int res = -1;
        int GOAL = MAKE_STATE(Keycnt, 0, 0);
        queue<Node> q;
        if (M[1][1] == S[0]) {
            q.push(Node(MAKE_STATE(1, 1, 1), 0));
            vis[1][1] = 1;
        } else {
            q.push(Node(MAKE_STATE(0, 1, 1), 0));
            vis[1][1] = 0;
        }
        while (!q.empty()) {
            Node cur = q.front();
            if ((cur.state & 0xffff0000) == GOAL) {
                res = cur.step;
                break;
            }
            q.pop();
            int px, py, pk;
            for (int ds = 0; ds < 4; ++ds) {
                px = PX(cur.state) + dx[ds];
                py = PY(cur.state) + dy[ds];
                pk = GOALKEY(cur.state);
                if (px < 1 || px > m || py < 1 || py > n)
                    continue;
                if (M[px][py] == 0)
                    continue;
                if (S[pk] == M[px][py])
                    ++pk;
                if (vis[px][py] >= pk)
                    continue;
                vis[px][py] = pk;
                q.push(Node(MAKE_STATE(pk, px, py), cur.step + 1));
            }
        }
        cout << res << endl;
    }
    return 0;
}