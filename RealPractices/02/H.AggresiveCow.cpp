#include <algorithm>
#include <iostream>
using namespace std;

int n, m;
int a[100004];

bool check(int x) {
    // The first cow must be put into a[0]
    int last = 0;
    for (int i = 1; i < m; i++) {
        int pos = last + 1;
        while (pos < n && a[pos] - a[last] < x)
            pos++;
        if (pos == n)
            return false;
        last = pos;
    }
    return true;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    sort(a, a + n);

    int l = 0;
    int r = numeric_limits<int>::max();
    while (r - l > 1) {
        int mid = (l + r) / 2;
        if (check(mid))
            l = mid;
        else
            r = mid;
    }
    printf("%d\n", l);
}