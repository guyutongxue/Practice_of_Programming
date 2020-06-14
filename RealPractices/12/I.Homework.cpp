// blg15288 课程大作业 ，状态压缩动归  by guo wei
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Homework {
    string name;
    int d;  // 截止时间
    int c;  // 要花的时间
};
Homework hw[20];

struct Node {
    int pre;  // 上一个状态，状态就是已经完成的作业的集合。（比当前状态完成的作业少了1个）
    int minScore;   // 当前状态的最小扣分数
    int last;       // 当前状态下，最后完成的作业的编号
    int finishDay;  // 作业 last 完成的时间
};

Node dp[(1 << 16) + 20];

// 获取从状态 0 到状态 status 的路径
vector<int> getPath(int status) {
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
        for (int i{0}; i < n; ++i) {
            cin >> hw[i].name >> hw[i].d >> hw[i].c;
        }
        dp[0] = {-1, 0, 0, 0};
        int m{1 << n};  // m-1 是全部作业都完成的状态
        for (int i{1}; i < m; ++i) {
            dp[i].minScore = 1 << 30;
            for (int j{0}; j < n; ++j) {  //输入排过序了，序号大的作业就是字典序大的作业
                if (i & (1 << j)) {         // m包含作业j ，则考察从 {m}-j 变到 {m}
                    int pre{i - (1 << j)};  // pre就是状态m中去掉作业j的状态
                    // 要求 dp[i] 时，任何 dp[pre] 肯定已经算出了,因为 pre < i
                    int finishDay{dp[pre].finishDay + hw[j].c};
                    int tmpScore{finishDay - hw[j].d};
                    if (tmpScore < 0)
                        tmpScore = 0;
                    if (dp[i].minScore > dp[pre].minScore + tmpScore) {
                        dp[i] = {pre, dp[pre].minScore + tmpScore, j, finishDay};
                    } else if (dp[i].minScore == dp[pre].minScore + tmpScore) {
                        // 发现了一个同样优的做法，要比较字典序
                        vector<int> p1(getPath(dp[i].pre));
                        vector<int> p2(getPath(pre));
                        if (p2 < p1) {
                            dp[i].pre = pre;
                            dp[i].finishDay = finishDay;
                            dp[i].last = j;
                        }
                    }
                }
            }
        }
        cout << dp[m - 1].minScore << endl;
        vector<int> path(getPath(m - 1));

        for (int i{0}; i < path.size(); ++i) {
            cout << hw[path[i]].name << endl;
        }
    }
}
