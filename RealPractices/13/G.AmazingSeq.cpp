#include <cstring>
#include <iostream>
using namespace std;
int score[202][202];
int N;
int num[202];
int main() {
    int T;
    scanf("%d", &T);
    int T0 = T;
    while (T--) {
        memset(score, 1, sizeof(score));
        memset(num, 0, sizeof(num));
        int N;
        scanf("%d", &N);  // cin >> N;
        for (int i = 0; i < N; ++i) {
            scanf("%d", &num[i]);  // cin >> num[i];
            score[i][i] = 1;
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < i; ++j) {
                score[i][j] = 0;
            }
        }
        for (int i = 0; i < N - 1; ++i) {
            if (num[i] == num[i + 1])
                score[i][i + 1] = 1;
            else
                score[i][i + 1] = 2;
        }
        for (int i = N - 2; i >= 0; --i) {
            for (int j = i + 1; j < N; ++j) {
                for (int k = i; k < j; ++k) {
                    if (num[k] == num[j]) {
                        score[i][j] = min(score[i][j], score[i][k] + score[k + 1][j - 1]);
                    }
                    score[i][j] = min(score[i][j], score[i][k] + score[k + 1][j]);
                }
            }
        }
        printf("Case %d: %d\n", T0 - T, score[0][N - 1]);
    }
    return 0;
}