#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int age;
    int no;
    int averageGrade[4];
    double result;

public:
    void input() {
        getline(cin, name, ',');
        cin >> age;
        cin.ignore();
        cin >> no;
        cin.ignore();
        for (int i = 0; i < 4; i++) {
            cin >> averageGrade[i];
            cin.ignore();
        }
    }
    void calculate() {
        result = 0.;
        for (int i = 0; i < 4; i++) {
            result += averageGrade[i];
        }
        result /= 4;
    }
    void output() {
        cout << name << "," << age << "," << no << "," << result << endl;
    }
};

int main() {
    Student student;      // 定义类的对象
    student.input();      // 输入数据
    student.calculate();  // 计算平均成绩
    student.output();     // 输出数据
}