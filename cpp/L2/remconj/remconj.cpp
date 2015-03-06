/*************************************************************************
	> File Name: remconj.cpp
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Thu 05 Mar 2015 07:03:22 PM CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<sstream>
#include<cctype>

int main(int argc, char **argv)
{
	std::string str;
	std::string sstr;
	std::string sumstr;

	std::cout<<"Input a string:";
	getline(std::cin, str);

	for(std::string::iterator ix = str.begin();ix < str.end();ix++)
	{
		if(ispunct(*ix))
			*ix = ' ';
	}

	std::cout<<std::endl;


	std::istringstream istr(str);

	while(istr>>sstr)
		sumstr += sstr;

	std::cout<<sumstr<<std::endl;

	return 0;
}
