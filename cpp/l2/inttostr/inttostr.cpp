/*************************************************************************
	> File Name: inttostr.cpp
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Thu 05 Mar 2015 06:36:17 PM CST
 ************************************************************************/

#include<iostream>
#include<string>

std::string integerToString(int a)
{
	std::string str;

	int i = -1;

	while(a)
	{
		str[++i] = a % 10 + '0';
		a /= 10;
	}

	str[++i] = '\0';

	while(i)
		std::cout<<str[--i];

	return str;
}

int main(int argc, char **argv)
{
	int x;
	std::string str;

	std::cout<<"Input a num:";
	std::cin>>x;
	std::cout<<std::endl;

	str = integerToString(x);

	for(std::string::iterator ix = str.end();ix != str.begin();ix--)
		std::cout<<*ix;

	std::cout<<std::endl;

	return 0;
}
