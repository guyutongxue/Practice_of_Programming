#include <algorithm>
#include <cstring>
#include <iostream>
#include <limits>
using namespace std;
int8_t oriboard[16] = {};
int8_t board[16] = {};
int8_t operation[16] = {};

void setBit(int8_t& buf, int pos, bool value) {
    if (value) {
        buf &= ~(1 << pos);
    } else {
        buf |= 1 << pos;
    }
}

int main() {
    int n;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 6; ++j) {
            int c;
            cin >> c;
            setBit(oriboard[i], j, !c);
        }
    }
    int ans = numeric_limits<int>::max();
    for (int x = 0; x < (1 << 6); ++x) {
        int current = x;
        int step = 0;
        memcpy(board, oriboard, sizeof(oriboard));
        for (int i = 0; i < 5; ++i) {
            operation[i] = current;
            for (int j = 0; j < 6; ++j) {
                if (current & (1 << j)) {
                    ++step;
                    if (j > 0)
                        board[i] ^= 1 << (j - 1);
                    board[i] ^= 1 << j;
                    if (j < 6 - 1)
                        board[i] ^= 1 << (j + 1);
                }
            }
            if (i < 5 - 1)
                board[i + 1] ^= current;
            current = board[i];
        }
        if (board[5 - 1] == 0) {
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 6; j++) {
                    cout << !!(operation[i] & (1 << j)) << " \n"[j == 5];
                }
            }
        }
    }
}