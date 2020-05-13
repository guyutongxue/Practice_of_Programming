#include <iostream>
#include <list>
#include <string>
using namespace std;

class A {
private:
    string name;

public:
    A(string n) : name(n) {}
    friend bool operator<(const A& a1, const A& a2);
    friend bool operator==(const A& a1, const A& a2) {
        if (a1.name.size() == a2.name.size())
            return true;
        else
            return false;
    }
    friend ostream& operator<<(ostream& o, const A& a) {
        o << a.name;
        return o;
    }
    string get_name() const {
        return name;
    }
    int get_size() const {
        return name.size();
    }
};
#include<iterator>
bool operator<(const A& a1, const A& a2) {
    return a1.name.size() < a2.name.size();
}
template<typename T>
struct MyLarge {
    bool operator()(const T& a,const T& b) const {
        return a.get_name().at(0) < b.get_name().at(0);
    }
};

ostream_iterator<string> Print() {
    return ostream_iterator<string>(cout," ");
}
void Show(const list<A>::iterator& a,const list<A>::iterator& b, ostream_iterator<string> c) {
    for(auto i = a; i != b; ++i, ++c) {
        *c = i->get_name();
    }
}

int main(int argc, char* argv[]) {
    list<A> lst;
    int ncase, n, i = 1;
    string s;
    cin >> ncase;
    while (ncase--) {
        cout << "Case: " << i++ << endl;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> s;
            lst.push_back(A(s));
        }
        lst.sort();
        Show(lst.begin(), lst.end(), Print());

        cout << endl;
        lst.sort(MyLarge<A>());
        Show(lst.begin(), lst.end(), Print());
        cout << endl;
        lst.clear();
    }
    return 0;
}