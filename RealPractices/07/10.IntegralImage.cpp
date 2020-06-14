// COPIED


#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
class IntegralImage {
public:
    int h, w;
    int c{0};
    int* p;
    IntegralImage(int h, int w) : h{h}, w{w} {
        p = new int[h * w];
        for (int i = 0; i < h * w; i++) {
            p[i] = 0;
        }
    }
    void operator()(int* t) {
        for (int j = 0; j < w; j++) {
            if (c >= 1)
                p[c * w + j] = p[(c - 1) * w + j];
            for (int k = 0; k <= j; k++) {
                p[c * w + j] += t[k];
            }
        }
        c++;
    }
    int* operator[](int n) {
        return p + n * w;
    }
};
int main() {
    int H, W;
    cin >> H >> W;
    int** image = new int*[H];
    for (int i = 0; i < H; ++i) {
        image[i] = new int[W];
    }
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
            cin >> image[i][j];
    IntegralImage it(H, W);
    for_each(image, image + H, it);
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j)
            cout << it[i][j] << " ";
        cout << endl;
    }
}