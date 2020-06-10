// 爷也抑郁了

#include <cstring>
#include <iostream>
using namespace std;
int a[7], n;
bool dfs(int* a, int len) {
    if (len == 1 && a[1] == 42)
        return true;
    int b[7]{};
    memset(b, 0, sizeof(b));
    for (int i{1}; i < len; i++)
        for (int j{i + 1}; j <= len; j++) {
            int p{1};
            for (int k{1}; k <= len; k++) {
                if (k != i && k != j)
                    b[p++] = a[k];
            }
            b[p] = a[i] + a[j];
            if (dfs(b, len - 1))
                return true;
            b[p] = a[i] * a[j];
            if (dfs(b, len - 1))
                return true;
            b[p] = a[i] - a[j];
            if (dfs(b, len - 1))
                return true;
            b[p] = a[j] - a[i];
            if (dfs(b, len - 1))
                return true;
            if (a[j] != 0 && a[i] % a[j] == 0) {
                b[p] = a[i] / a[j];
                if (dfs(b, len - 1))
                    return true;
            }
            if (a[i] != 0 && a[j] % a[i] == 0) {
                b[p] = a[j] / a[i];
                if (dfs(b, len - 1))
                    return true;
            }
        }
    return false;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cout << (dfs(a, n) ? "YES" : "NO") << endl;
}