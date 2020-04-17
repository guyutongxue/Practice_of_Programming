#include <functional>
#include <iostream>
#include <queue>
using namespace std;

class Clock {
private:
    int m;

public:
    void operator++(int) {
        m++;
        if (m == 4)
            m = 0;
    }
    operator int() {
        return m;
    }
    friend istream& operator>>(istream&, Clock&);
};

istream& operator>>(istream& i, Clock& c) {
    i >> c.m;
    return i;
}

struct Wall {
    Clock a, b, c, d, e, f, g, h, i;
};

function<void(Wall&)> action[10] = {
    [](Wall&) {},
    [](Wall& wall) { wall.a++, wall.b++, wall.d++, wall.e++; },
    [](Wall& wall) { wall.a++, wall.b++, wall.c++; },
    [](Wall& wall) { wall.b++, wall.c++, wall.e++, wall.f++; },
    [](Wall& wall) { wall.a++, wall.d++, wall.g++; },
    [](Wall& wall) { wall.b++, wall.d++, wall.e++, wall.f++, wall.h++; },
    [](Wall& wall) { wall.c++, wall.f++, wall.i++; },
    [](Wall& wall) { wall.d++, wall.e++, wall.g++, wall.h++; },
    [](Wall& wall) { wall.g++, wall.h++, wall.i++; },
    [](Wall& wall) { wall.e++, wall.f++, wall.h++, wall.i++; },
};

bool check(Wall& wall) {
    return wall.a == 0 && wall.b == 0 && wall.c == 0 && wall.d == 0 && wall.e == 0 && wall.f == 0 &&
           wall.g == 0 && wall.h == 0 && wall.i == 0;
}

int cnt[9] = {};

void dfs(int k, Wall wall) {
    if (k > 9) {
        if (check(wall)) {
            for (int i = 1; i <= 9; i++) {
                while (cnt[i]--) {
                    cout << i << " \n"[i == 9 && cnt[i] == 0];
                }
            }
            exit(0);
        }
        return;
    }
    for (int i = 0; i <= 3; i++) {
        cnt[k] = i;
        dfs(k + 1, wall);
        action[k](wall);
    }
}

int main() {
    ios::sync_with_stdio(false);
    Wall root;
    cin >> root.a >> root.b >> root.c >> root.d >> root.e >> root.f >> root.g >> root.h >> root.i;
    dfs(1, root);
}