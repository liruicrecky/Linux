/*************************************************************************
	> File Name: comstr.cpp
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Thu 05 Mar 2015 06:20:35 PM CST
 ************************************************************************/

#include<iostream>
#include<string>

int main(int argc, char *argv[])
{
	std::string str;
	std::string sstr;
	
	while(getline(std::cin, str))
	{
		sstr += str + "$";
	}
	
	*(sstr.end() - 1) = '\0';

	std::cout<<sstr<<std::endl;

	return 0;
}
