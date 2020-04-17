#include <algorithm>
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;
constexpr int&& INF = std::numeric_limits<int>::max();
int a[120][1100];

// 状态转移方程：dp[i][j] = min(dp[i][j], dp[i-1][k]+q)
// dp[i][j]表示前i组带宽为j的最小价格
int main() {
    int n;
    cin >> n;
    while (n--) {
        int m;
        cin >> m;
        for (int i = 1; i <= m; i++) {
            for (int j = 0; j < 1100; j++) {
                a[i][j] = INF;
            }
        }
        for (int i = 1; i <= m; i++) {
            int num;
            cin >> num;
            for (int j = 0; j < num; j++) {
                int p, q;
                cin >> p >> q;
                if (i == 1) {
                    a[i][p] = min(a[1][p], q);
                } else {
                    // 之所以从0遍历到1200：
                    // 1. 预估带宽最大到1200
                    // 2. 保证所有的带宽与对应的最小价格都被存到二维数组中,最后所求最小价格即为a[3][min带宽]
                    for (int k = 0; k < 1100; k++) {
                        if (a[i - 1][k] != INF) {
                            if (k <= p)
                                a[i][k] = min(a[i][k], a[i - 1][k] + q);
                            else
                                a[i][p] = min(a[i][p], a[i - 1][k] + q);
                            
                        }
                    }
                }
            }
        }
        double res = 0;
        for (int i = 0; i < 1100; i++) {
            if (a[m][i] != INF) {
                double temp = 1.* i / a[m][i];
                res = max(res,temp);
            }
        }
        cout<<fixed<<setprecision(3)<<res;
    }
    return 0;
}