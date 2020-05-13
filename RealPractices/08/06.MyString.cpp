#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

class MyString {
    char* p;

public:
    MyString() {
        p = new char[1]{'\0'};
    }
    MyString(const char* s) {
        if (s) {
            p = new char[strlen(s) + 1];
            strcpy(p, s);
        } else
            p = nullptr;
    }
    ~MyString() {
        if (p)
            delete[] p;
    }
    MyString(const MyString& s) {
        if (s.p) {
            p = new char[strlen(s.p) + 1];
            strcpy(p, s.p);
        } else
            p = nullptr;
    }
    MyString& operator=(const MyString& s) {
        if (p == s.p)
            return *this;
        if (p)
            delete[] p;
        if (s.p) {
            p = new char[strlen(s.p) + 1];
            strcpy(p, s.p);
        } else
            p = nullptr;
        return *this;
    }
    char& operator[](int i) const {
        return *(p + i);
    }
    MyString operator()(int pos, int len) const {
        if (!p)
            throw "WTF";
        char* np = new char[len + 1];
        for (int i = 0; i < len; ++i) {
            np[i] = p[i + pos];
        }
        np[len] = '\0';
        MyString result(np);
        delete[] np;
        return result;
    }
    MyString operator+(const MyString& s) const {
        if (!s.p)
            return *this;
        char* np = new char[strlen(p) + strlen(s.p) + 1];
        strcpy(np, p);
        strcat(np, s.p);
        MyString result(np);
        delete[] np;
        return result;
    }
    MyString& operator+=(const MyString& s) {
        if (!s.p)
            return *this;
        char* np = nullptr;
        if (p)
            np = new char[strlen(p) + strlen(s.p) + 1];
        else
            np = new char[strlen(s.p) + 1];
        strcpy(np, p);
        strcat(np, s.p);
        delete[] p;
        p = np;
        return *this;
    }
    bool operator<(const MyString& s) const {
        return strcmp(p, s.p) < 0;
    }
    bool operator==(const MyString& s) const {
        return strcmp(p, s.p) == 0;
    }
    bool operator>(const MyString& s) const {
        return strcmp(p, s.p) > 0;
    }
    friend ostream& operator<<(ostream&, const MyString&);
    friend MyString operator+(const char*, const MyString&);
};
ostream& operator<<(ostream& o, const MyString& s) {
    o << s.p;
    return o;
}
MyString operator+(const char* c, const MyString& s) {
    if (!s.p)
        return MyString(c);
    char* np = new char[strlen(c) + strlen(s.p) + 1];
    strcpy(np, c);
    strcat(np, s.p);
    MyString result(np);
    delete[] np;
    return result;
}
int CompareString( const void * e1, const void * e2)
{
	MyString * s1 = (MyString * ) e1;
	MyString * s2 = (MyString * ) e2;
	if( * s1 < *s2 )
		return -1;
	else if( *s1 == *s2)
		return 0;
	else if( *s1 > *s2 )
		return 1;
}
int main()
{
	MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
	MyString SArray[4] = {"big","me","about","take"};
	cout << "1. " << s1 << s2 << s3<< s4<< endl;
	s4 = s3;
	s3 = s1 + s3;
	cout << "2. " << s1 << endl;
	cout << "3. " << s2 << endl;
	cout << "4. " << s3 << endl;
	cout << "5. " << s4 << endl;
	cout << "6. " << s1[2] << endl;
	s2 = s1;
	s1 = "ijkl-";
	s1[2] = 'A' ;
	cout << "7. " << s2 << endl;
	cout << "8. " << s1 << endl;
	s1 += "mnop";
	cout << "9. " << s1 << endl;
	s4 = "qrst-" + s2;
	cout << "10. " << s4 << endl;
	s1 = s2 + s4 + " uvw " + "xyz";
	cout << "11. " << s1 << endl;
	qsort(SArray,4,sizeof(MyString),CompareString);
	for( int i = 0;i < 4;i ++ )
	cout << SArray[i] << endl;
	//s1的从下标0开始长度为4的子串
	cout << s1(0,4) << endl;
	//s1的从下标5开始长度为10的子串
	cout << s1(5,10) << endl;
	return 0;
}