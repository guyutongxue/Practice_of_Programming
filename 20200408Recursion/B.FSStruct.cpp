#include <iostream>
#include <queue>
using namespace std;

struct Directory {
    string name;
    int depth;
    Directory(string name, int depth) : name(name), depth(depth) {
        set();
    }
    vector<Directory*> subdir;
    priority_queue<string, vector<string>, greater<string>> files;
    void set() {
        string input;
        while (cin >> input, input[0] != '*') {
            if (input == "]")
                return;
            if (input[0] == 'f')
                files.push(input);
            else if (input[0] == 'd')
                subdir.push_back(new Directory(input, depth + 1));
        }
    }
    void print() {
        for (int j = 0; j < depth; ++j)
            cout << "|     ";
        cout << name << endl;
        for (auto& i : subdir) {
            // for (int j = 0; j < depth; ++j)
            //     cout << "|     ";
            i->print();
        }
        auto temp = files;
        while (!temp.empty()) {
            for (int j = 0; j < depth; ++j)
                cout << "|     ";
            cout << temp.top() << endl;
            temp.pop();
        }
    }
};

int main() {
    int t = 0;
    while (true) {
        if (cin.peek() == '\n')
            cin.ignore();
        if (cin.peek() == '#')
            return 0;
        cout << "DATA SET " << ++t << ":" << endl;
        Directory root("ROOT", 0);
        root.print();
        cout << endl;
    }
}