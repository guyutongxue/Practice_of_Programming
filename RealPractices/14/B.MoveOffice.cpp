#include <iostream>
#include <algorithm>
using namespace std;
/**
 * @brief 
 * 0: bj, 1: nj
 */
int f[102][2]{};
int bj[102]{}, nj[102]{};
int main() {
    int t,m;
    cin >> t >> m;
    for(int i{1}; i<= t; i++) {
        cin >> bj[i] >> nj[i];
    }
    f[1][0] = bj[1];
    f[1][1] = nj[1]; 
    for(int i{2}; i<= t; i++) {
        f[i][0] = max(f[i - 1][0], f[i - 1][1] - m) + bj[i];
        f[i][1] = max(f[i - 1][1], f[i - 1][0] - m) + nj[i];
    }
    cout << max(f[t][0], f[t][1]) << endl;
}