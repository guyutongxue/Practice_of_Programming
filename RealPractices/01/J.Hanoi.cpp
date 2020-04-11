#include <iostream>
using namespace std;
void act(int num, char start, char end, char assist) {
    if (num == 1) {
        cout << start << "->1->" << end << endl;
        return;
    }
    act(num - 1, start, assist, end);
    cout << start << "->" << num << "->" << end << endl;
    act(num - 1, assist, end, start);
}
int main() {
    int n;
    char a, b, c;
    cin >> n >> a >> b >> c;
    act(n, a, b, c);
}