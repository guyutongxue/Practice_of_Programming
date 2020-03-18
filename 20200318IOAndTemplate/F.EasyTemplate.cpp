#include <cstring>
#include <iostream>
#include <string>
using namespace std;
template <class T>
class myclass {
    T* p = nullptr;
    int size;
public:
    myclass(const T* pos, int len) {
        p = new T[len];
        size = len;
        memcpy(p, pos, sizeof(T) * len);
    }
    ~myclass() {
        delete[] p;
    }
    void Show() {
        for (int i = 0; i < size; i++) {
            cout << p[i] << ",";
        }
        cout << endl;
    }
};
int a[100];
int main() {
    char line[100];
    while (cin >> line) {
        myclass<char> obj(line, strlen(line));
        ;
        obj.Show();
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        myclass<int> obj2(a, n);
        obj2.Show();
    }
    return 0;
}