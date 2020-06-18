#include <cstring>
#include <iostream>
using namespace std;
bool map[1005][1005]{};
bool v[1005]{};
int n, m;
bool k;
void dfs(int x) {
    if (k)
        return;
    for (int i{0}; i < n; i++) {
        if (map[x][i] && !v[i]) {
            v[i] = true;
            dfs(i);
            v[i] = false;
        } else if (map[x][i])
            k = true;
    }
}
int main() {
    while (cin >> n >> m) {
        k = false;
        memset(map, 0, sizeof(map));
        memset(v, 0, sizeof(v));
        while (m--) {
            int a, b;
            cin >> a >> b;
            map[a][b] = true;
        }
        for (int i{0}; i < n; i++) {
            dfs(i);
        }
        if (k)
            cout << "False" << endl;
        else
            cout << "True" << endl;
    }
}