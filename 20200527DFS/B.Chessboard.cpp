// POJ 1321

#include <cstring>
#include <iostream>
using namespace std;

int n, k;
char board[10][10];
bool visited[10];

int find(int row, int current) {
    if (current >= k)
        return 1;
    int result = 0;
    for (int i = row; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == '#' && !visited[j]) {
                visited[j] = true;
                result += find(i + 1, current + 1);
                visited[j] = false;
            }
        }
    }
    return result;
}

int main() {
    while (cin >> n >> k, n != -1) {
        memset(board, '.', sizeof(board));
        for (int i = 0; i < n; i++) {
            cin >> board[i];
        }
        cout << find(0, 0) << endl;
    }
}
