#include <iostream>
using namespace std;
class CMyClassA {
    int val;

public:
    CMyClassA(int);
    void virtual print();
};
CMyClassA::CMyClassA(int arg) {
    val = arg;
    printf("A:%d\n", val);
}
void CMyClassA::print() {
    printf("%d\n", val);
    return;
}
class CMyClassB : public CMyClassA {
    int val2;

public:
    CMyClassB(int val2) : CMyClassA(3 * val2), val2(val2) {
        printf("B:%d\n", val2);
    }
    void print() {
        printf("%d\n", val2);
    }
};
int main(int argc, char** argv) {
    CMyClassA a(3), *ptr;
    CMyClassB b(5);
    ptr = &a;
    ptr->print();
    a = b;
    a.print();
    ptr = &b;
    ptr->print();
    return 0;
}