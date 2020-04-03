#include <algorithm>
#include <cstring>
#include <iostream>
#include <limits>
using namespace std;
int16_t oriboard[16] = {};
int16_t board[16] = {};
int16_t operation[16] = {};

void setBit(int16_t& buf, int pos, bool value) {
    if (value) {
        buf &= ~(1 << pos);
    } else {
        buf |= 1 << pos;
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char c;
            cin >> c;
            setBit(oriboard[i], j, c != 'w');
        }
    }
    int ans = numeric_limits<int>::max();
    for (int x = 0; x < (1 << n); ++x) {
        int current = x;
        int step = 0;
        memcpy(board, oriboard, sizeof(oriboard));
        for (int i = 0; i < n; ++i) {
            operation[i] = current;
            for (int j = 0; j < n; ++j) {
                if (current & (1 << j)) {
                    ++step;
                    if (j > 0)
                        board[i] ^= 1 << (j - 1);
                    board[i] ^= 1 << j;
                    if (j < n - 1)
                        board[i] ^= 1 << (j + 1);
                }
            }
            if (i < n - 1)
                board[i + 1] ^= current;
            current = board[i];
        }
        if (board[n - 1] == 0) {
            ans = min(ans, step);
        }
    }
    if (ans == numeric_limits<int>::max())
        cout << "inf" << endl;
    else
        cout << ans << endl;
}