#include <iostream>
#include <algorithm>
#include <bitset>
using namespace std;
int main() {
    int a, b, i, j;
    cin >> a >> b >> i >> j;
    if (i > j) swap(i,j);
    //                j      i
    // convert: 00...0111...1100..0
    int convert = ((1 << i) - 1) ^ ((1 << (j+1)) - 1);
    // comp: reverse the i~j bit
    int comp = b ^ convert;
    // part: make other bit 0
    int part = comp & convert;
    // adeal: make a's i~j to 1, then reverse them
    int adeal = a | convert;
    adeal ^= convert;
    cout << (adeal | part) << endl;
}