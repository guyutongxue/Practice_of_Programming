#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct Patient {
    int id;
    int priority;
    Patient(int a, int b) : id(a), priority(b) {}
    bool operator<(const Patient& b) const {
        return priority == b.priority ? id > b.id : priority < b.priority;
    }
};
int main() {
    int t, n;
    priority_queue<Patient, vector<Patient>, less<Patient>> q[3];
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n;
        string str, cmd;
        int doc, priority;
        int id = 0;
        for (int j = 0; j < n; j++) {
            cin >> cmd;
            if (cmd == "IN") {
                cin >> doc >> priority;
                q[doc - 1].push(Patient(++id, priority));
            } else {
                cin >> doc;
                if (q[doc - 1].empty())
                    cout << "EMPTY" << endl;
                else {
                    cout << q[doc - 1].top().id << endl;
                    q[doc - 1].pop();
                }
            }
        }
        for (int k = 0; k < 3; k++)
            while (!q[k].empty())
                q[k].pop();
    }
    return 0;
}