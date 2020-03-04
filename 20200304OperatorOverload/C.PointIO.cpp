#include <iostream>
using namespace std;
class Point {
private:
    int x;
    int y;

public:
    Point(){};
    friend istream& operator>>(istream&, Point&);
    friend ostream& operator<<(ostream&, const Point&);
};
istream& operator>>(istream& i, Point& p) {
    i >> p.x >> p.y;
    return i;
}
ostream& operator<<(ostream& o, const Point& p) {
    o << p.x << ',' << p.y;
    return o;
}
int removeThatFuckingBrace[1] = {};
int main() {
    Point p;
    while (cin >> p) {
        cout << p << endl;
    }
    return 0;
}