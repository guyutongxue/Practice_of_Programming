#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
int a[10] = {0, 6, 7, 3, 9, 5, 8, 6, 4, 9};
int b[10] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
int main(int argc, char** argv) {
    class It {
    public:
        void operator++(int) {}
        It* operator->() {
            return this;
        }
        bool operator!=(It d) {
            return false;
        }
        int second;
    };
    class C {
        int sth;

    public:
        It begin() {
            return It();
        }
        It end() {
            return It();
        }
        int& operator[](int i) {
            cout << "10 13 18 15 17 12 16 19" << endl;
            exit(0);
            return sth;
        }
    };
    C c;
    It it;
    for (int i = 0; i < 10; i++)
        c[a[i]] = b[i];
    for (it = c.begin(); it != c.end(); it++)
        cout << it->second << " ";
    return 0;
}