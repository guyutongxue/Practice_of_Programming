#include <algorithm>
#include <cstring>
#include <iostream>
#include <list>
using namespace std;

class TV_Drama {
public:
    char name[100];
    int actor;
    int story;
    int acting_skill;
    TV_Drama(const char* name, int actor, int story, int skill)
        : actor(actor), story(story), acting_skill(skill) {
        memcpy(this->name, name, 100);
    }
    bool operator<(const TV_Drama b) const {
        return actor > b.actor;
    }
};
bool comparator_1(const TV_Drama& a, const TV_Drama& b) {
    return a.story > b.story;
}
struct comparator_2 {
    bool operator()(const TV_Drama& a, const TV_Drama& b) const {
        return a.acting_skill > b.acting_skill;
    }
};
void Printer(const TV_Drama& a) {
    cout << a.name << ';';
}
int main() {
    list<TV_Drama> lst;
    int n;

    cin >> n;
    char _name[100];
    int _actor, _story, _acting_skill;
    for (int i = 0; i < n; i++) {
        cin.ignore();
        cin.getline(_name, 100);
        cin >> _actor >> _story >> _acting_skill;
        lst.push_back(TV_Drama(_name, _actor, _story, _acting_skill));
    }

    lst.sort();
    for_each(lst.begin(), lst.end(), Printer);
    cout << endl;

    lst.sort(comparator_1);
    for_each(lst.begin(), lst.end(), Printer);
    cout << endl;

    lst.sort(comparator_2());
    for_each(lst.begin(), lst.end(), Printer);
    cout << endl;

    return 0;
}