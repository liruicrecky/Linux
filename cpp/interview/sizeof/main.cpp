/*************************************************************************
	> File Name: main.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Thu 02 Apr 2015 03:13:31 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

struct s{
	unsigned short int a:5;
	unsigned short int b:5;
	unsigned short int c:6;
};

struct a{
	int f1:3;
	char b;
	char c;
};

int main(void)
{
	int (*n)[10];
	cout << sizeof(a) << endl;

	return 0;
}
