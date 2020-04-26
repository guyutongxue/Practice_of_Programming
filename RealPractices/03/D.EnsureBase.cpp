// Copied from IC-A/Mock-EndTerm/2
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int getMax(int p, int q, int r) {
    int res = -1;
    do {
        res = max(res, p % 10);
    } while (p /= 10);
    do {
        res = max(res, q % 10);
    } while (q /= 10);
    do {
        res = max(res, r % 10);
    } while (r /= 10);
    return res;
}

bool check(int p, int q, int r, int b) {
    int rp = 0, multi[10];
    multi[0] = 1;
    for (int i = 1; i <= 7; i++) {
        multi[i] = multi[i - 1] * b;
    }
    int i = 0;
    do {
        rp += (p % 10) * multi[i++];
    } while (p /= 10);
    i = 0;
    int rq = 0;
    do {
        rq += (q % 10) * multi[i++];
    } while (q /= 10);
    i = 0;
    int rr = 0;
    do {
        rr += (r % 10) * multi[i++];
    } while (r /= 10);
    // cout<<b<<": "<<rr<<" "<<rp<<" "<<rq<<endl;
    return rp * rq == rr;
}

int main() {
    ios::sync_with_stdio(false);
    // int t;
    // cin >> t;
    // while (t--) {
    int p, q, r;
    cin >> p >> q >> r;
    int b = getMax(p, q, r) + 1;
    while (b <= 1000000) {
        if (check(p, q, r, b))
            break;
        b++;
    }
    if (b > 1000000)
        cout << "0" << endl;
    else
        cout << b << endl;
    // }
    return 0;
}