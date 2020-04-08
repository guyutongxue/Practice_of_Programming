#include <cstring>
#include <iostream>
using namespace std;
char bitmap[2050][2050];

int n;

void paint(short left, short top, int depth) {
    if (depth == 1) {
        bitmap[top][left + 1] = '/';
        bitmap[top][left + 2] = '\\';
        bitmap[top + 1][left] = '/';
        bitmap[top + 1][left + 1] = '_';
        bitmap[top + 1][left + 2] = '_';
        bitmap[top + 1][left + 3] = '\\';
        return;
    }
    paint(left + (1 << (depth - 1)), top, depth - 1);
    paint(left, top + (1 << (depth - 1)), depth - 1);
    paint(left + (1 << depth), top + (1 << (depth - 1)), depth - 1);
}

void print() {
    for (int i = 0; i < (1 << n); ++i) {
        for (int j = 0; j <= (1 << n) + i; ++j) {
            cout << bitmap[i][j];
        }
        cout << endl;
    }
}

int main() {
    while (cin >> n, n) {
        memset(bitmap, ' ', sizeof(bitmap));
        paint(0, 0, n);
        print();
        cout << endl;
    }
}