#include <array>
#include <iostream>
#include <set>
using namespace std;

template <int n>
array<array<bool, n>, n> generate(const array<array<int, n>, n>& src) {
    array<array<bool, n>, n> res;
    for (int i{0}; i < n; i++) {
        for (int j{0}; j < n; j++) {
            res[i][j] = src[i][j] > 50;
        }
    }
    return res;
}

array<array<int, 110>, 110> a;
set<pair<int, int>> ans;

int main() {
    int n;
    cin >> n;
    for (int i{0}; i < 110; i++) {
        a[i][i] = 100;
    }
    for (int i{0}; i < n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        a[x][y] = z;
    }
    auto first = generate<110>(a);
    for (int i{0}; i < 110; i++) {
        for (int j{0}; j < 110; j++) {
            if (first[i][j]) {
                ans.insert({i, j});
            }
        }
    }

    auto backup(a);

    for (int i{0}; i < 110; i++) {
        for (int j{0}; j < 110; j++) {
            int s{0};
            for (int k{0}; k < 110; k++) {
                s += first[i][k] * backup[k][j];
            }
            a[i][j] = s;
        }
    }

    auto second = generate<110>(a);
    for (int i{0}; i < 110; i++) {
        for (int j{0}; j < 110; j++) {
            if (second[i][j]) {
                ans.insert({i, j});
            }
        }
    }
    for (auto i : ans) {
        if (i.first == i.second)
            continue;
        cout << i.first << ' ' << i.second << endl;
    }
}