#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Mat {
    int h, w;

public:
    Mat(int height, int width) : h(height), w(width) {
        number = count++;
    }
    vector<int> p;
    static int count;
    int number;
    ~Mat() {
        number--;
    }
    bool operator<(const Mat& b) const {
        return h * w == b.h * b.w ? number > b.number : h * w < b.h * b.w;
    }
    int sum() const {
        int res = 0;
        for (int i = 0; i < h * w; i++) {
            res += p[i];
        }
        return res;
    }
    friend istream& operator>>(istream&, Mat&);
    friend ostream& operator<<(ostream&, const Mat&);
};
istream& operator>>(istream& i, Mat& m) {
    for (int j = 0; j < m.h * m.w; j++) {
        int x;
        cin >> x;
        m.p.push_back(x);
    }
    return i;
}
ostream& operator<<(ostream& o, const Mat& m) {
    for (int i = 0; i < m.h * m.w; i++) {
        o << m.p[i] << " \n"[!((i + 1) % m.w)];
    }
    return o;
}
int Mat::count = 0;
#include <functional>
bool comparator_1(const Mat& a, const Mat& b) {
    return a.sum() == b.sum() ? a.number > b.number : a.sum() < b.sum();
}

function<bool(const Mat& a, const Mat& b)> comparator_2() {
    return [](const Mat& a, const Mat& b) { return a.number < b.number; };
}

int main() {
    vector<Mat> m;
    m.push_back(Mat(2, 2));
    m.push_back(Mat(3, 4));
    m.push_back(Mat(2, 2));
    cin >> m[0] >> m[1] >> m[2];
    sort(m.begin(), m.end());
    cout << m[0] << endl << m[1] << endl << m[2] << endl;
    cout << "*************" << endl;
    sort(m.begin(), m.end(), comparator_1);
    cout << m[0] << endl << m[1] << endl << m[2] << endl;
    cout << "*************" << endl;
    sort(m.begin(), m.end(), comparator_2());
    cout << m[0] << endl << m[1] << endl << m[2] << endl;
    return 0;
}