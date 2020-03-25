#include <cmath>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>

void calculate(std::string& t, std::stack<double>& num) {
    double num1 = num.top();
    num.pop();
    double num2 = num.top();
    num.pop();
    if (t == "+")
        num.push(num2 + num1);
    if (t == "-")
        num.push(num2 - num1);
    if (t == "*")
        num.push(num2 * num1);
    if (t == "/")
        num.push(num2 / num1);
    if (t == "^")
        num.push(pow(num2, num1));
}

int main() {
    int n;
    std::cin >> n;

    std::priority_queue<double, std::vector<double>, std::greater<double>> mem;
    std::stack<double> num;
    for (int i = 1; i <= n; i++) {
        double w;
        std::cin >> w;
        mem.push(w);
    }
    std::cin.ignore();
    std::string command;
    while (std::getline(std::cin, command)) {
        std::stringstream ss;
        ss << command;
        std::string t;
        while (ss >> t) {
            if (t == "=") {
                printf("%e\n", num.top());
                mem.pop();
                mem.push(num.top());
                num.pop();
            } else {
                if (t != "+" && t != "*" && t != "-" && t != "/" && t != "^")
                    num.push(std::stod(t));
                else
                    calculate(t, num);
            }
        }
    }
    printf("\n");

    int count = 0;
    for (int i = 1; i <= n; i++) {
        count++;
        if (i == n)
            std::printf("%e", mem.top());
        else if (count % 10 == 0)
            std::printf("%e\n", mem.top());
        else
            std::printf("%e ", mem.top());
        mem.pop();
    }
    return 0;
}