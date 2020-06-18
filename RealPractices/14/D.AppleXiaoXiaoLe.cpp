#include <iostream>
#include <algorithm>
using namespace std;

int a[105]{};
int pre[105]{};

int main() {
    int t;
    cin >> t;
    while(t--) {
        int n,m;
        cin >> n >> m;
        if(m > n) m = n;
        int last{0};
        for(int i{0}; i<n; i++) {
            int next;
            cin >> next;
            a[i] = next - last - 1;
            last = next;
        }
        a[n] = 100 - last;
        pre[0] = 0;
        for(int i{0}; i <= n; i++) {
            // cout << a[i] << " ";
            pre[i + 1] = pre[i] + a[i];
        }
        int ans{-1};
        for(int i{m + 1}; i <= n + 1; i++) {
            ans = max(ans, pre[i] - pre[i-m-1]);
        }
        cout << ans + m << endl;
    }
}