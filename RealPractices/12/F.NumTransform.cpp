
#include <iostream>
#include <limits>
#include <queue>

using namespace std;

int storage[100000][4][3]{};

struct Node {
    int num;
    int m2;  // times of operation 2
    int m3;  // times of operation 3
    int step;
};

queue<Node> q;

void bfs() {
    q.push({12345, 0, 0, 0});
    while (!q.empty()) {
#if __cplusplus >= 201709L
        auto [num, m2, m3, s] = q.front();
#else
        Node n = q.front();
        int num = n.num, m2 = n.m2, m3 = n.m3, s = n.step;
#endif
        q.pop();
        if (storage[num][m2][m3])
            continue;
        storage[num][m2][m3] = s;
        int a[5]{};
        for (int& i : a) {
            i = num % 10;
            num /= 10;
        }
        auto genNum = [&a](int w, int k, int h, int d, int s) {
            return a[w] * 10000 + a[k] * 1000 + a[h] * 100 + a[d] * 10 + a[s];
        };
        // Operation 1
        q.push({genNum(3, 4, 2, 1, 0), m2, m3, s + 1});
        q.push({genNum(4, 2, 3, 1, 0), m2, m3, s + 1});
        q.push({genNum(4, 3, 1, 2, 0), m2, m3, s + 1});
        q.push({genNum(4, 3, 2, 0, 1), m2, m3, s + 1});

        // Operation 2
        if (m2 < 3) {
            for (int i{0}; i < 5; ++i) {
                int tmp = a[i];
                a[i] = (a[i] + 1) % 10;
                q.push({genNum(4, 3, 2, 1, 0), m2 + 1, m3, s + 1});
                a[i] = tmp;
            }
        }

        // Operation 3
        if (m3 < 2) {
            for (int i{0}; i < 5; ++i) {
                int tmp = a[i];
                a[i] = (a[i] * 2) % 10;
                q.push({genNum(4, 3, 2, 1, 0), m2, m3 + 1, s + 1});
                a[i] = tmp;
            }
        }
    }
}

int main() {
    bfs();
    int x;
    while (cin >> x) {
        if (x == 12345) {
            cout << 0 << endl;
            continue;
        }
        int ans = numeric_limits<int>::max();
        for (int i{0}; i <= 3; ++i) {
            for (int j{0}; j <= 2; ++j) {
                if (storage[x][i][j])
                    ans = min(ans, storage[x][i][j]);
            }
        }
        if (ans == numeric_limits<int>::max())
            cout << -1 << endl;
        else
            cout << ans << endl;
    }

    return 0;
}