#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

int a[100005];
int profit1[100005];
int profit2[100005];

int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        memset(profit1, 0, sizeof(profit1));
        memset(profit2, 0, sizeof(profit2));
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i){
            cin >> a[i];
        }

        // Find the biggest profit from day 0 to day i
        int mina = a[0]; // Minimum a[j] in 0 ... i
        for (int i = 1; i < n; ++i) {
            mina = min(mina, a[i]);
            profit1[i] = max(profit1[i - 1], a[i] - mina);
        }
        
        // Find the biggest profit from day i to day n - 1
        int maxa = a[n - 1]; // Maximum a[j] in i ... n - 1
        for (int i = n - 1; i >= 0; --i) {
            maxa = max(maxa, a[i]);
            profit2[i] = max(profit2[i - 1], maxa - a[i]);
        }

        int ans = 0;
        for (int i = 0; i < n; ++i)
            ans = max(ans, profit1[i] + profit2[i]);
        cout << ans << endl;
    }
}