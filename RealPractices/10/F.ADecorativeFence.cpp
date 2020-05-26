// POJ 1037

// COPIED, original by Guo Wei.

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstring>

using namespace std;
const int UP = 0;
const int DOWN = 1;
int64_t C[25][25][2];  // C[i][k][DOWN] 是S(i)中以第k短的木棒打头的DOWN方案数,C[i][k][UP]
                       // 是S(i)中以第k短的木棒打头的UP方案数,第k短指i根中第k短
void init(int n) {
    memset(C, 0, sizeof(C));
    C[1][1][UP] = C[1][1][DOWN] = 1;
    for (int i = 2; i <= n; ++i)
        for (int k = 1; k <= i; ++k) {   //枚举第一根木棒的长度
            for (int M = k; M < i; ++M)  //枚举第二根木棒的长度
                C[i][k][UP] += C[i - 1][M][DOWN];
            for (int N = 1; N <= k - 1; ++N)  //枚举第二根木棒的长度
                C[i][k][DOWN] += C[i - 1][N][UP];
        }
    //总方案数是 Sum{ C[n][k][DOWN] + C[n][k][UP] } k = 1.. n;
}
void print(int n, int64_t cc) {
    int64_t skipped = 0;  //已经跳过的方案数
    int seq[25];          //最终要输出的答案
    int used[25];         //木棒是否用过
    memset(used, 0, sizeof(used));
    for (int i = 1; i <= n; ++i) {  //依次确定每一个位置i的木棒序号
        int64_t oldVal = skipped;
        int k;
        int No = 0;                 // k是剩下的木棒里的第No短的,No从1开始算
        for (k = 1; k <= n; ++k) {  //枚举位置i的木棒 ，其长度为k
            oldVal = skipped;
            if (!used[k]) {
                ++No;  // k是剩下的木棒里的第No短的
                if (i == 1)
                    skipped += C[n][No][UP] + C[n][No][DOWN];
                else {
                    if (k > seq[i - 1] && (i <= 2 || seq[i - 2] > seq[i - 1]))  //合法放置
                        skipped += C[n - i + 1][No][DOWN];
                    else if (k < seq[i - 1] && (i <= 2 || seq[i - 2] < seq[i - 1]))  //合法放置
                        skipped += C[n - i + 1][No][UP];
                }
                if (skipped >= cc)
                    break;
            }
        }
        used[k] = true;
        seq[i] = k;
        skipped = oldVal;
    }
    for (int i = 1; i <= n; ++i)
        if (i < n)
            printf("%d ", seq[i]);
        else
            printf("%d", seq[i]);
    printf("\n");
}
int main() {
    int t, n;
    int64_t c;
    init(20);
    scanf("%d", &t);
    while (t--) {
        scanf("%d %lld", &n, &c);
        print(n, c);
    }
    return 0;
}
