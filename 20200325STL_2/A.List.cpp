#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::map<int, std::vector<int>> m;

int main() {
    int n;
    std::cin >> n;
    while (n--) {
        std::string command;
        std::cin >> command;
        if (command == "new") {
            int id;
            std::cin >> id;
            m.insert(std::make_pair(id, std::vector<int>()));
        } else if (command == "add") {
            int id, num;
            std::cin >> id >> num;
            auto& temp = m[id];
            temp.push_back(num);
        } else if (command == "merge") {
            int id1, id2;
            std::cin >> id1 >> id2;
            if(id1==id2){
                // Ok, Thanks Liu Jun Qi
                continue;
            }
            auto& v1 = m[id1];
            auto& v2 = m[id2];
            v1.insert(v1.end(), v2.begin(), v2.end());
            v2.clear();
        } else if (command == "unique") {
            int id;
            std::cin >> id;
            auto& temp = m[id];
            std::sort(temp.begin(), temp.end());
            temp.erase(std::unique(temp.begin(), temp.end()), temp.end());
        } else if (command == "out") {
            int id;
            std::cin >> id;
            auto& temp = m[id];
            std::sort(temp.begin(), temp.end());
            for (auto i = temp.begin(); i != temp.end(); ++i) {
                std::cout << *i;
                if (i != temp.end() - 1)
                    std::cout << ' ';
            }
            std::cout << std::endl;
        }
    }
}