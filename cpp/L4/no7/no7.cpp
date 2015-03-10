/*************************************************************************
	> File Name: no7.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Tue 10 Mar 2015 11:06:56 AM CST
 ************************************************************************/

#include<iostream>

using std::cout;
using std::endl;

class A
{
	int a;
	static int b;
};
class B
{
	int a;
	char b;
};
class C
{
	float a;
	char b;
};
class D
{
	float a;
	int b;
	char c;
};
class E
{
	double a;
	float b;
	int c;
	char d;
};

int main(void)
{
	cout << (sizeof(A)) << endl;
	cout << (sizeof(B)) << endl;
	cout << (sizeof(C)) << endl;
	cout << (sizeof(D)) << endl;
	cout << (sizeof(E)) << endl;

	return 0;
}

