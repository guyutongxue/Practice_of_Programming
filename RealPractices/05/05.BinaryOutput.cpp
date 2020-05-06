#include <iostream>
#include <string>
using namespace std;
string dec2bin(int x){
    string res(31,'0');
    for(int i=0;i<31;i++){
        res[i]=((x>>(30-i))&1)+'0';
    }
    return res;
}
int main(){
	int n;
	cin >> n;
	while(n--) {
		int x;
		cin >> x;
		cout << dec2bin(x) << endl;
	}
	return 0;
}