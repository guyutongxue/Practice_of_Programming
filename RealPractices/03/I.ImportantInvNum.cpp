#include <cstring>
#include <iostream>
using namespace std;
// 声明这个别名就是让 int* const 这种写法好看一点
// 感觉写成 const Ptr<int> 比 int* const 好
template <typename T>
using Ptr = T*;
long long mergeSort(const Ptr<int> begin, const Ptr<int> end) {
    if (begin + 1 == end)
        return 0ll;
    const Ptr<int> mid = begin + (end - begin) / 2;
    long long result = 0ll;
    result += mergeSort(begin, mid);
    result += mergeSort(mid, end);
    // cout<<"old "<<result;
    int* pa = begin;
    int* pb = mid;
    while (pa < mid) {
        while (pb < end && 2 * (*pb) >= *pa)
            pb++;
        result += end - pb;
        pa++;
    }
    // cout<<"new "<<result<<endl;
    pa = begin;
    pb = mid;
    const Ptr<int> tmp = new int[end - begin];
    int* pr = tmp;
    while (pa < mid || pb < end) {
        if (pa == mid)
            *pr++ = *pb++;
        else if (pb == end)
            *pr++ = *pa++;
        else if (*pa > *pb)
            *pr++ = *pa++;
        else if (*pa <= *pb)
            *pr++ = *pb++;
    }
    memcpy(begin, tmp, (end - begin) * sizeof(int));
    // delete[] tmp;
    return result;
}
int a[200002];
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cout << mergeSort(a, a + n) << endl;
}