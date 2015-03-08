/*************************************************************************
	> File Name: 5_20.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Sun 08 Mar 2015 09:07:55 PM CST
 ************************************************************************/

#include<iostream>

using std::cout;
using std::cin;
using std::endl;

int main(void)
{
	int i, j;

	cout << "Input two numbers: ";
	cin >> i >> j;

	cout << "The min number is: " << (i > j ? j : i) << endl;

	return 0;
}
