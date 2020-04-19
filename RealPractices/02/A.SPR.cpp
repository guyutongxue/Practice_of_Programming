#include <cstring>
#include <iostream>
using namespace std;

struct Player {
    int* p;
    int size;
    int current;
    Player(int n) : size(n), current(0) {
        p = new int[n];
    }
    void set(int* arr) {
        memcpy(p, arr, size * sizeof(int));
    }
    operator int() {
        return p[current];
    }
    int operator++() {
        current++;
        if (current == size)
            current = 0;
        return p[current];
    }
    ~Player() {
        delete[] p;
    }
};

// a lose -1
// draw 0
// a win 1
int judge(int a, int b) {
    if (a == b)
        return 0;
    if (a == 0 && b == 5)
        return -1;
    if (a == 5 && b == 0)
        return 1;
    else
        return a < b ? 1 : -1;
}

int main() {
    int n, na, nb;
    cin >> n >> na >> nb;
    Player a(na), b(nb);
    int temp[105];
    for (int i = 0; i < na; i++) {
        cin >> temp[i];
    }
    a.set(temp);
    for (int i = 0; i < nb; i++) {
        cin >> temp[i];
    }
    b.set(temp);
    int counta = 0, countb = 0;
    for (int i = 1; i <= n; i++) {
        switch (judge(a, b)) {
            case -1: countb++; break;
            case 1: counta++; break;
        }
        ++a, ++b;
    }
    if (counta > countb)
        cout << 'A' << endl;
    else if (counta < countb)
        cout << 'B' << endl;
    else
        cout << "draw" << endl;
}