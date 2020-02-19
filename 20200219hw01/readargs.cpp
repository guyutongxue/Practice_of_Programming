#include <cstring>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    cout << atoi(argv[1]) + atoi(argv[argc - 1]) << endl;
}