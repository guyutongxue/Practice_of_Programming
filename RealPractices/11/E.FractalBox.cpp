// Same as RP03/G

#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
char bitmap[800][800];

void draw(int depth, int top, int left, bool isEdge) {
    if (depth == 1) {
        bitmap[top][left] = 'X';
        if (isEdge)
            bitmap[top][left + 1] = '\0';
        return;
    }
    int tab = pow(3, depth - 2);
    draw(depth - 1, top, left, false);
    draw(depth - 1, top, left + 2 * tab, isEdge);
    draw(depth - 1, top + tab, left + tab, isEdge);
    draw(depth - 1, top + 2 * tab, left, false);
    draw(depth - 1, top + 2 * tab, left + 2 * tab, isEdge);
}

int main() {
    int n;
    while (cin >> n, n != -1) {
        memset(bitmap, ' ', sizeof(bitmap));
        draw(n, 0, 0, true);
        for (int i = 0; i < (int)pow(3, n - 1); i++) {
            cout << bitmap[i] << endl;
        }
        cout << "-" << endl;
    }
}