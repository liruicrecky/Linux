/*************************************************************************
	> File Name: no6.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Tue 10 Mar 2015 11:03:58 AM CST
 ************************************************************************/

#include<iostream>

class A
{
	bool a;
	int b;
	bool c;
};
class B
{
	int a;
	bool b;
	bool c;
};

int main(void)
{
	std::cout << (sizeof(A)) << std::endl;
	std::cout << (sizeof(B)) << std::endl;
	return 0;
}
