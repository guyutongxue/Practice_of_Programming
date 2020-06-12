// dfs

#include <iostream>
#include <vector>
using namespace std;

const double EPS = 1e-6;
vector<int> solution;

inline bool isEqual(double a) {
    return (a <= 1 + EPS && a >= 1 - EPS);
}

bool dfs(double sum, int now, int left) {
    if (sum + 1. / left > 1 + EPS)
        return false;
    if (isEqual(sum + 1. / left)) {
        solution.push_back(left);
        return true;
    }
    for (int i = now; i < left - 1; i++) {
        solution.push_back(i);
        if (dfs(sum + 1. / i, i, left - i))
            return true;
        solution.pop_back();
    }
    return false;
}

int main() {
    int m;
    cin >> m;
    while (m--) {
        solution.clear();
        int s;
        cin >> s;
        if (dfs(0, 1, s)) {
            cout << solution.size();
            for (auto& i : solution) {
                cout << " " << i;
            }
            cout << endl;
        } else {
            cout << -1 << endl;
        }
    }
    return 0;
}