/*************************************************************************
	> File Name: no5.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Tue 10 Mar 2015 10:57:44 AM CST
 ************************************************************************/

#include<iostream>

class A
{
public:
	A(int n) { value = n;}
	A(A &other) { value = other.value;}
	void print()
	{
		std::cout << value << std::endl;
	}
private:
	int value;
};

int main(void)
{
	A a(10);
	A b(a);
	b.print();
	return 0;
}
