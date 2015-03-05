/*************************************************************************
	> File Name: traverstr.cpp
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Thu 05 Mar 2015 05:29:36 PM CST
 ************************************************************************/

#include<iostream>
#include<string>

int main(int argc, char *argv[])
{
	std::string str;

	std::cout<<"Input a string:";
	std::cin>>str;

	std::cout<<std::endl<<"ori:";

	for(std::string::iterator ix = str.begin();ix < str.end();ix++)
		std::cout<<*ix;

	std::cout<<std::endl<<"res:";

	for(std::string::iterator ix = str.begin();ix < str.end();ix++)
	{
		if(*ix >= 'a' && *ix <= 'z')
			*ix -= 32;
		else if(*ix >= 'A' && *ix <= 'Z')
			*ix += 32;
		std::cout<<*ix;
	}

	std::cout<<std::endl<<std::endl;
	
	return 0;
}
