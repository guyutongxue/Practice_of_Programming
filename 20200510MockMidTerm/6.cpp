#include <iostream>
#include <iterator>
using namespace std;

template<class T1, class T2>
void Copy(T1 s, T1 e, T2 x) {
    for(; s != e; ++s, ++x)
        *x = *s;
}
int getFib(int x) {
    if (x < 3) return 1;
    int a = 1;
    int b = 1;
    for(int i=3;i<=x;i++) {
        b = a + b;
        swap(a,b);
    }
    return a;
}
struct Fib {
    int x;
    Fib( int x) : x(x) {}
    bool operator!=(const Fib& b) const {
        return x != b.x;
    }
    Fib operator++() {
        x++;
        return *this;
    }
    int operator*() {
        return getFib(x);
    }
};
int main() {
	while(true) {
		int n;
		cin >> n;
		if(n == 0)
			break;
		
	    Fib f1(1), f2(n);
	    ostream_iterator<int> it(cout, " ");
	    Copy(f1, f2, it);
	    cout << endl;
	}
	return 0;
}