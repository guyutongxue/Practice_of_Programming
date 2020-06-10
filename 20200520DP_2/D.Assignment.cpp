// blg15288 

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

struct Assignment {
    string name;
    int d;
    int c;
};
Assignment a[20];

struct Node {
    int32_t pre;
    int minscore;
    int32_t last;
    int finishday;
};
Node dp[(1 << 16) + 20];

vector<int> getpath(int status) {
    vector<int> path;
    while (status) {
        path.push_back(dp[status].last);
        status = dp[status].pre;
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> a[i].name >> a[i].d >> a[i].c;
        }
        dp[0].finishday = 0;
        dp[0].minscore = 0;
        dp[0].pre = -1;
        int m = 1 << n;
        for (int i = 1; i <= m; ++i) {
            dp[i].minscore = 1 << 30;
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j)) {
                    int pre = i - (1 << j);
                    int finishday = dp[pre].finishday + a[j].c;
                    int tmpscore = finishday - a[j].d;
                    if (tmpscore < 0)
                        tmpscore = 0;
                    if (dp[i].minscore > dp[pre].minscore + tmpscore) {
                        dp[i].minscore = dp[pre].minscore + tmpscore;
                        dp[i].pre = pre;
                        dp[i].finishday = finishday;
                        dp[i].last = j;
                    }
                    if (dp[i].minscore == dp[pre].minscore + tmpscore) {
                        vector<int> p1 = getpath(dp[i].pre);
                        vector<int> p2 = getpath(pre);
                        if (p2 < p1) {
                            dp[i].pre = pre;
                            dp[i].finishday = finishday;
                            dp[i].last = j;
                        }
                    }
                }
            }
        }
        cout << dp[m - 1].minscore << endl;
        int status = m - 1;
        vector<int> path = getpath(status);
        for (int i = 0; i < path.size(); ++i)
            cout << a[path[i]].name << endl;
    }

    return 0;
}