#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
using namespace std;
// Inherit is a good feature.
template <typename T1, typename T2, typename T3 = greater<T1>>
class MyMultimap : public multimap<T1, T2, T3> {
public:
    void Set(const T2& a, const T1& b) {
        int cnt = 0;
        for (auto i = this->begin(); i != this->end(); ++i) {
            if (i->second == a) {
                this->erase(i);
                cnt++;
            }
        }
        while (cnt--) {
            this->insert(make_pair(b, a));
        }
    }
    void Set(const T1& a, const T2& b) {
        for (auto i = this->begin(); i != this->end(); ++i) {
            if (i->first == a) {
                i->second = b;
            }
        }
    }
};
template <typename T1, typename T2>
ostream& operator<<(ostream& o, std::pair<T1, T2> a) {
    o << '(' << a.first << ',' << a.second << ')';
    return o;
}
struct Student {
    string name;
    int score;
};
template <class T>
void Print(T first, T last) {
    for (; first != last; ++first)
        cout << *first << ",";
    cout << endl;
}
int main() {
    Student s[] = {{"Tom", 80}, {"Jack", 70}, {"Jone", 90}, {"Tom", 70}, {"Alice", 100}};

    MyMultimap<string, int> mp;
    for (int i = 0; i < 5; ++i)
        mp.insert(make_pair(s[i].name, s[i].score));
    Print(mp.begin(), mp.end());  //按姓名从大到小输出

    mp.Set("Tom", 78);  //把所有名为"Tom"的学生的成绩都设置为78
    Print(mp.begin(), mp.end());

    MyMultimap<int, string, less<int>> mp2;
    for (int i = 0; i < 5; ++i)
        mp2.insert(make_pair(s[i].score, s[i].name));

    Print(mp2.begin(), mp2.end());  //按成绩从小到大输出
    mp2.Set(70, "Error");           //把所有成绩为70的学生，名字都改为"Error"
    Print(mp2.begin(), mp2.end());
    cout << "******" << endl;

    mp.clear();

    string name;
    string cmd;
    int score;
    while (cin >> cmd) {
        if (cmd == "A") {
            cin >> name >> score;
            if (mp.find(name) != mp.end()) {
                cout << "erroe" << endl;
            }
            mp.insert(make_pair(name, score));
        } else if (cmd == "Q") {
            cin >> name;
            MyMultimap<string, int>::iterator p = mp.find(name);
            if (p != mp.end()) {
                cout << p->second << endl;
            } else {
                cout << "Not Found" << endl;
            }
        }
    }
    return 0;
}