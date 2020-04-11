// Copied from IC-Course/P3-2/9
#include <iomanip>
#include <iostream>
using namespace std;
int m, n, cnt, res;
void search(int k, int sup) {
    if (k > n) {
        if (res == m)
            cnt++;
        return;
    }
    for (int i = sup; i >= 0; i--) {
        res += i;
        search(k + 1, i);
        res -= i;
    }
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> m >> n;
        cnt = 0;
        res = 0;
        search(1, m);
        cout << cnt << endl;
    }
    return 0;
}