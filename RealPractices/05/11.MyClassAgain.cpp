#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
template <typename T>
class CMyClass {
    T* p;

public:
    CMyClass(T* a, int l) {
        p = new T[l];
        memcpy(p, a, sizeof(T) * l);
    }
    T& operator[](int x) {
        return p[x];
    }
    ~CMyClass() {
        delete[] p;
    }
};
int a[40];
int main(int argc, char** argv) {
    int t;
    scanf("%d", &t);
    while (t--) {
        int m;
        scanf("%d", &m);
        for (int i = 0; i < m; ++i)
            scanf("%d", a + i);
        char s[100];
        scanf("%s", s);
        CMyClass<int> b(a, m);
        CMyClass<char> c(s, strlen(s));
        printf("%d %c\n", b[5], c[7]);
    }
    return 0;
}