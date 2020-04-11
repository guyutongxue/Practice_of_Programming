#include <algorithm>
#include <iostream>
using namespace std;
struct Node {
    int x, y;
    bool operator<(const Node& b) const {
        return x == b.x ? y < b.y : x < b.x;
    }
};
Node p[5100];
int n, r, c;
inline bool inside(int x, int y) {
    return x > 0 && x <= r && y > 0 && y <= c;
}
bool binarySearch(int x, int y) {
    int low = 0, mid, high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (p[mid].x == x && p[mid].y == y)
            return true;
        if (p[mid].x < x || (p[mid].x == x && p[mid].y < y))
            low = mid + 1;
        else
            high = mid - 1;
    }
    return false;
}
int main() {
    cin >> r >> c >> n;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
    }
    sort(p, p + n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int x = p[j].x - p[i].x;
            int y = p[j].y - p[i].y;
            if (inside(p[i].x - x, p[i].y - y) || !inside(p[j].x + ans * x, p[j].y + ans * y))
                continue;
            int num = 0;
            for (int k = 1; inside(p[j].x + k * x, p[j].y + k * y); k++) {
                if (binarySearch(p[j].x + k * x, p[j].y + k * y))
                    num++;
                else {
                    num = 0;
                    break;
                }
            }
            ans = max(ans, num);
        }
    }
    if (ans)
        ans += 2;
    cout << ans << endl;

    return 0;
}