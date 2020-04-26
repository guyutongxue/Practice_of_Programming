// Copied from IC-A/P3-3/1
#include <cstring>
#include <iostream>
using namespace std;
double calculate() {
    char str[10];
    cin >> str;
    switch (str[0]) {
        case '+': {
            double a = calculate();
            return a + calculate();
        }
        case '-': {
            double a = calculate();
            return a - calculate();
        }
        case '*': {
            double a = calculate();
            return a * calculate();
        }
        case '/': {
            double a = calculate();
            return a / calculate();
        }
        default: return atof(str);
    }
}
int main() {
    printf("%f\n", calculate());
    return 0;
}