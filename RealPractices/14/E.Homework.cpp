/*
POJ 1456
贪心处理。
按照获利p从大到小排序。
处理的时候选择最后的一个不冲突点。

用并查集实现链表的作用，快速找到不冲突点
*/
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
int f[10010];
struct Node {
    int p, d;
};
Node node[10010];
int find(int x) {
    if (f[x] == -1)
        return x;
    return f[x] = find(f[x]);
}
int main() {
    int n;
    cin >> n;
    memset(f, -1, sizeof(f));
    for (int i{0}; i < n; i++) {
        cin >> node[i].p >> node[i].d;
    }
    sort(node, node + n, [](const Node& a, const Node& b) { return a.p > b.p; });
    int ans{0};
    for (int i{0}; i < n; i++) {
        int t = find(node[i].d);
        if (t > 0) {
            ans += node[i].p;
            f[t] = t - 1;
        }
    }
    cout << ans << endl;
    return 0;
}