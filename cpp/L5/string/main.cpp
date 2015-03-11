/*************************************************************************
	> File Name: ./main.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Wed 11 Mar 2015 04:03:02 PM CST
 ************************************************************************/

#include"string.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(void)
{
	char name[] = "li";
	char name1[] = "wang";

	String str(name);
	String str1(name1);

	cout << str << endl;
	cout << str1 << endl;
	
	cin >> str;
	cout << str << endl;

	if(str == str1)
		cout << "==";
	else if(str > str1)
		cout << ">";
	else if(str < str1)
		cout << "<";

	cout << endl;
//	str1 = name;

//	str.print();
//	str1.print();

//	cout << str1[1] << endl;

	return 0;
}
