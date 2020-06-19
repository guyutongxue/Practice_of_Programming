#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

bool map[12][12]{};
bool visited[12]{};
int n;

bool dfs(int k) {
    if (k == n) {
        return true;
    }
    for (int i{1}; i <= n; i++) {
        if (map[k][i] && !visited[i]) {
            visited[i] = true;
            if (dfs(i))
                return true;
        }
    }
    return false;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        memset(visited, false, sizeof(visited));
        for (int i{1}; i <= n; i++) {
            for (int j{1}; j <= n; j++) {
                int t;
                cin >> t;
                map[i][j] = t > 0;
            }
        }
        cout << (dfs(1) ? "YES" : "NO" )<< endl;
    }
}