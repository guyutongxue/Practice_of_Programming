// POJ 2373

#include <cstring>
#include <iostream>
#include <queue>
#include <limits>

/**********************************\
 *       STRONGLY RECOMMEND       *
 * -------------------------------*
 * View the video tutorial at     *
 * https://2d.hep.com.cn/187723/9 *
\**********************************/

using namespace std;
const int INF = numeric_limits<int>::max();

/**
 * f: DP
 * [x: a position]
 * Returns: How many springklers need to installed at least in interval (0, x)
 * More info can be found in the video.
 */
int f[1000002];

/**
 * cows: data
 * [position]
 * Returns: How many cows' range overlapped this dot
 */
int cows[1000002];

/**
 * cowVary: For calculating array cows[]
 * More info can be found in the video. 
 */
int cowVary[1000002];

/**
 * @brief Store (x, f(x)) pair for priority_queue.
 * 
 */
struct Fx {
    int x, f;
    bool operator<(const Fx &a) const {
        return f > a.f;
    }
    Fx(int x = 0, int f = 0) : x(x), f(f) {}
};

// See the video
priority_queue<Fx> q;


int main() {
    int n, l, a, b;
    cin >> n >> l >> a >> b;
    a <<= 1;
    b <<= 1;
    memset(cowVary, 0, sizeof(cowVary));
    for (int i = 0; i < n; i++) {
        int s, e;
        cin >> s >> e;
        ++cowVary[s + 1];
        --cowVary[e];
    }
    for (int i = 0,inCows = 0; i <= l; i++) {
        f[i] = INF;
        inCows += cowVary[i];
        cows[i] = inCows;
    }
    for (int i = a; i <= b; i += 2) {
        if (!cows[i]) {
            f[i] = 1;
            if (i <= b + 2 - a)
                q.push(Fx(i, 1));
        }
    }
    for (int i = b + 2; i <= l; i += 2) {
        if (!cows[i]) {
            Fx fx;
            while (!q.empty()) {
                fx = q.top();
                if (fx.x < i - b) {
                    q.pop();
                } else {
                    break;
                }
            }
            if (!q.empty())
                f[i] = fx.f + 1;
        }
        if (f[i - a + 2] != INF) {
            q.push(Fx(i - a + 2, f[i - a + 2]));
        }
    }
    if (f[l] == INF)
        cout << -1 << endl;
    else
        cout << f[l] << endl;
    return 0;
}