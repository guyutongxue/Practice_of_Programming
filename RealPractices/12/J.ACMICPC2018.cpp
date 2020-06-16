#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn{50007};
int n, m, p, k;
int t[maxn], u[maxn], numv[maxn];
int vt[maxn], vu[maxn];
int vx[maxn], vy[maxn], vz[maxn];
int dp[maxn];
int dp2[maxn];
struct Point {
    int x, y, z;
};
Point pp[maxn];
int main() {
    int css;
    cin >> css;
    while (css--) {
        scanf("%d%d%d", &n, &m, &p);
        k = 50000;
        int cnt = 1;
        for (int i = 1; i <= n; i++) {
            scanf("%d%d%d", &t[i], &u[i], &numv[i]);
            for (int j = 1; j <= numv[i]; j *= 2) {
                vt[cnt] = t[i] * j;
                vu[cnt++] = u[i] * j;
                numv[i] -= j;
            }
            if (numv[i]) {
                vt[cnt] = t[i] * numv[i];
                vu[cnt++] = u[i] * numv[i];
            }
        }
        memset(dp, 0, sizeof(dp));
        memset(dp2, 0, sizeof(dp2));
        for (int i = 1; i < cnt; i++) {
            for (int j = 50020; j >= vu[i]; j--) {
                dp[j] = max(dp[j], dp[j - vu[i]] + vt[i]);
            }
        }
        cnt = 1;
        for (int i = 1; i <= m; i++) {
            scanf("%d%d%d", &pp[i].x, &pp[i].y, &pp[i].z);
            for (int j = 1; j <= pp[i].z; j *= 2) {
                vx[cnt] = pp[i].x * j;
                vy[cnt++] = pp[i].y * j;
                pp[i].z -= j;
            }
            if (pp[i].z > 0) {
                vx[cnt] = pp[i].x * pp[i].z;
                vy[cnt++] = pp[i].y * pp[i].z;
            }
        }
        for (int i = 1; i < cnt; i++) {
            for (int j = 50020; j >= vy[i]; j--) {
                dp2[j] = max(dp2[j], dp2[j - vy[i]] + vx[i]);
            }
        }
        // printf("%d\n",dp2[12]);
        int ans1 = -1, ans2 = -1;
        for (int i = 1; i <= 50020; i++) {
            if (dp[i] >= p) {
                ans1 = i;
                break;
            }
        }
        if (dp[k] < ans1) {
            printf("FAIL\n");
        } else {
            for (int i = 1; i <= k; i++) {
                if (dp2[i] >= ans1) {
                    ans2 = i;
                    break;
                }
            }
            printf("%d\n", ans2);
        }
    }
}