#include <cmath>
#include <iostream>
using namespace std;

using lint = long long;

lint x[5] = {0, 0, 0, 1, 1};
lint y[5] = {0, 0, 1, 1, 0};

lint decide(int l, lint m) {
    lint area = (1LL << 2 * l) / 4;
    lint partNo = (m - 1) / area;
    return partNo + 1;
}

lint findY(int, lint);
lint findX(int l, lint m) {
    if (l == 1) {
        return x[m];
    }
    lint partNo = decide(l, m);
    lint sum = 1LL << 2 * l;
    lint a = 1LL << l - 1;
    switch (partNo) {
        case 1: return findY(l - 1, m);
        case 2: return findX(l - 1, m - sum / 4);
        case 3: return a + findX(l - 1, m - sum / 4 * 2);
        default: return a + a - 1 - findY(l - 1, sum + 1 - m);
    }
}

lint findY(int l, lint m) {
    if (l == 1) {
        return y[m];
    }
    int partNo = decide(l, m);
    lint sum = 1LL << 2 * l;
    lint a = 1LL << l - 1;
    switch (partNo) {
        case 1: return findX(l - 1, m);
        case 2: return a + findY(l - 1, m - sum / 4);
        case 3: return a + findY(l - 1, m - sum / 4 * 2);
        default: return findX(l - 1, sum + 1 - m);
    }
}

int main() {
    int num;
    int level;
    lint m, n;
    cin >> num;
    while (num--) {
        cin >> level >> m >> n;
        lint x1 = findX(level, m);
        lint y1 = findY(level, m);
        lint x2 = findX(level, n);
        lint y2 = findY(level, n);
        lint dis = round(sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) * 10);
        cout << dis << endl;
    }
}