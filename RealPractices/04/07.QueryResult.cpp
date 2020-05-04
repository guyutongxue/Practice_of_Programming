#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;
void QueryResult(const map<int,list<int>>::iterator a,const map<int,list<int>>::iterator b) {
    for(auto i =a;i != b; i++) {
        cout << i->first ;
        if(i->second.empty())continue;
        cout << ':';
        for(auto j = i->second.begin();j!=i->second.end();j++) {
            cout << ' ' << *j ;
        }
        cout << endl;    
    }
}
int main(int argc, char* argv[]) {
    map<int, list<int>> Attendance;
    map<int, list<int>>::iterator it;
    string cmd;
    int date, id, date_lower, date_upper;
    while (cin >> cmd) {
        if (cmd == "add") {
            cin >> date >> id;
            it = Attendance.find(date);
            if (it != Attendance.end()) {
                it->second.push_back(id);
            } else {
                list<int> lst_id;
                lst_id.push_back(id);
                Attendance.insert(make_pair(date, lst_id));
            }
        } else if (cmd == "query") {
            cin >> date_lower >> date_upper;
            QueryResult(Attendance.lower_bound(date_lower), Attendance.upper_bound(date_upper));
        } else if (cmd == "exit")
            return 0;
    }
    return 0;
}