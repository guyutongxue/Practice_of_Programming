#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
int ori = 0;
int lock = 0;
int dest = 0;
void setBit(int& buf, int pos, bool value) {
    if (value)
        buf |= (1 << pos);
    else
        buf &= ~(1 << pos);
}

void flipBit(int& buf, int pos) {
    buf ^= (1 << pos);
}

bool getBit(int buf, int pos) {
    return (buf >> pos) & 1;
}

int main() {
    char line[40];
    cin >> line;
    int n = strlen(line);
    for (int i = 0; i < n; ++i)
        setBit(ori, i, line[i] - '0');
    cin >> line;
    for (int i = 0; i < n; ++i)
        setBit(dest, i, line[i] - '0');
    int ans = 666;
    for (int x = 0; x < 2; ++x) {
        lock = ori;
        int steps = 0;
        bool curbutton = x;
        for (int i = 0; i < n; ++i) {
            if (curbutton) {
                ++steps;
                if (i > 0)
                    flipBit(lock, i - 1);
                flipBit(lock, i);
                if (i < n - 1)
                    flipBit(lock, i + 1);
            }
            curbutton = (getBit(lock, i) ^ getBit(dest, i));
        }
        if (lock == dest)
            ans = min(ans, steps);
    }
    if (ans == 666)
        cout << "impossible" << endl;
    else
        cout << ans << endl;
    return 0;
}