#include <cstdint>
#include <iostream>
using namespace std;
struct Rect {
    // left, right, top, height, width, area
    int64_t l, r, t, h, w, s;
};

istream& operator>>(istream& in, Rect& r) {
    in >> r.l >> r.t >> r.w >> r.h;
    r.r = r.l + r.w;
    r.s = r.w * r.h;
    return in;
}

Rect rects[10002];

int64_t r, n;
int64_t result(int64_t mid) {
    int64_t sum = 0;
    for (int64_t i = 1; i <= n; i++) {
        if (rects[i].r <= mid)  // whole in left
            sum += rects[i].s;
        else if (rects[i].l >= mid)  // whole in right
            sum -= rects[i].s;
        else  // divided into to parts, (m-l)-(m-r) = 2*m-l-r
            sum += rects[i].h * (2 * mid - rects[i].l - rects[i].r);
    }
    return sum;
}
int find(int64_t l, int64_t r) {
    if (l == r) {
        return l;
    }
    int64_t mid;
    mid = (l + r) / 2;
    if (result(mid) >= 0)
        return find(l, mid);
    else
        return find(mid + 1, r);
}
int main() {
    cin >> r >> n;
    for (int64_t i = 1; i <= n; i++) {
        cin >> rects[i];
    }
    int ans = find(0, r);
    while (result(ans) == result(ans + 1) && ans < r)
        ans++;
    cout << ans << endl;
    return 0;
}