#include <array>
#include <iostream>
#include <sstream>
#include <string>

std::array<std::string, 22> a;

int executeInt();
std::string executeString() {
    std::string command;
    std::cin >> command;
    if (command == "copy") {
        int n = executeInt();
        int x = executeInt();
        int l = executeInt();
        return a[n].substr(x, l);
    } else if (command == "add") {
        std::string s1 = executeString();
        std::string s2 = executeString();
        if ([&s1, &s2] {
                for (auto i : s1) {
                    if (!std::isdigit(i))
                        return false;
                }
                for (auto i : s2) {
                    if (!std::isdigit(i))
                        return false;
                }
                if (std::stoi(s1) > 99999 || std::stoi(s2) > 99999)
                    return false;
                return true;
            }()) {
            int result = std::stoi(s1) + std::stoi(s2);
            std::stringstream ss;
            ss << result;
            return ss.str();
        } else
            return s1 + s2;
    } else
        return command;
}

int executeInt() {
    std::string command;
    std::cin >> command;

    if (command == "find") {
        std::string s = executeString();
        int n = executeInt();
        size_t pos = a[n].find(s);
        if (pos == std::string::npos)
            return a[n].size();
        else
            return pos;
    } else if (command == "rfind") {
        std::string s = executeString();
        int n = executeInt();
        size_t pos = a[n].rfind(s);
        if (pos == std::string::npos)
            return a[n].size();
        else
            return pos;
    } else
        return std::stoi(command);
}

int main() {
    int N;
    std::cin >> N;
    for (int i = 1; i <= N; i++) {
        std::cin >> a[i];
    }
    std::string command;
    while (std::cin >> command, command != "over") {
        if (command == "insert") {
            std::string s = executeString();
            int n = executeInt();
            int x = executeInt();
            a[n].insert(x, s);
        } else if (command == "reset") {
            std::string s = executeString();
            int n = executeInt();
            a[n] = s;
        } else if (command == "print") {
            int n = executeInt();
            std::cout << a[n] << std::endl;
        } else if (command == "printall") {
            for (int i = 1; i <= N; i++) {
                std::cout << a[i] << std::endl;
            }
        }
    }
}
/*
reset(add(copy(1, find("3", 1), 3), copy(2, find("2", 2), 2)), 3)


*/