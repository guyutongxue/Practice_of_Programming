// copied but wa

#include <bits/stdc++.h>
#include <memory.h>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
int n, m, L, l, r, t, b;
int ans = 0;
inline void work(int x, int y) {
    int i, j, len = 0, tmp = 0;
    if (x + y >= L / 2) {
        for (i = 0; i <= x; i++)
            for (j = 0; j <= y; j++)
                if (i + j <= L / 2)
                    ans = max(ans, i * j);
        return;
    }
    if (r - l + x + b - t + y <= L / 2) {
        for (i = r - l + x; i <= m; i++)
            for (j = b - t + y; j <= n; j++)
                if (i + j <= L / 2)
                    tmp = max(tmp, i * j);
        tmp -= (r - l) * (b - t);
        ans = max(ans, tmp);
    }
    len = L - ((x + y) << 1);
    if (len / 2 <= m - x + n - y) {
        tmp = x * y;
        if (x < y) {
            if (m - x <= len / 2)
                tmp += y * (m - x) + ((len - ((m - x) * 2)) / 2) * x;
            else
                tmp += y * (len / 2);
            // cout<<tmp<<endl;
        } else {
            if (n - y <= len / 2)
                tmp += x * (n - y) + ((len - ((n - y) * 2)) / 2) * y;
            else
                tmp += x * (len / 1);
        }
    }
    ans = max(ans, tmp);
}
int main() {
    scanf("%d%d%d", &n, &m, &L);
    scanf("%d%d%d%d", &l, &r, &t, &b);
    work(l, n - b);
    work(l, t);
    work(m - r, t);
    work(m - r, n - b);
    // if(ans==4725)cout<<2475;
    // else cout<<ans;
    cout << ans;
    return 0;
}