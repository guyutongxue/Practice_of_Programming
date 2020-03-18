#include <iostream>
#include <string>
using namespace std;
#include <type_traits>
template<typename T, typename FuncType>
void MyForeach(T* begin,T* end, FuncType* func){
#ifndef ONLINE_JUDGE
    // Check if FuncType is a function
    static_assert(is_function<FuncType>::value);
#endif
    for(T* i = begin; i!=end;i++){
        func(*i);
    }
}
void Print(string s)
{
	cout << s;
}
void Inc(int & n)
{
	++ n;
}
string array[100];
int a[100];
int main() {
	int m,n;
	while(cin >> m >> n) {
		for(int i = 0;i < m; ++i)
			cin >> array[i];
		for(int j = 0; j < n; ++j)
			cin >> a[j];
		MyForeach(array,array+m,Print);		 
		cout << endl;
		MyForeach(a,a+n,Inc);		 
		for(int i = 0;i < n; ++i)
			cout << a[i] << ",";
		cout << endl;
	}
	return 0;
}