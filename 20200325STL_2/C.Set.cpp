#include <algorithm>
#include <iostream>
#include <set>
#include <string>

std::multiset<int> set;
std::set<int> history;

int main() {
    int n;
    std::cin >> n;
    while (n--) {
        std::string command;
        std::cin >> command;
        if (command == "add") {
            int x;
            std::cin >> x;
            set.insert(x);
            history.insert(x);
            std::cout << set.count(x) << std::endl;
        } else if (command == "del") {
            int x;
            std::cin >> x;
            std::cout << set.count(x) << std::endl;
            auto pos = set.find(x);
            while (pos != set.end()){
                set.erase(pos);
                pos = set.find(x);
            }
        } else if (command == "ask") {
            int x;
            std::cin >> x;
            std::cout << (history.find(x) != history.end()) << ' ' << set.count(x) << std::endl;
        }
    }
}