/*************************************************************************
	> File Name: 6_20.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Sun 08 Mar 2015 10:57:41 PM CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<sstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(void)
{
	string str;
	string line;
	string tmp;

	int flag = 1;
	int findwor = 0;

	while(getline(cin, line))
	{
		std::istringstream istr(line);

		while(istr >> str)
		{
			if(flag == 1)
			{
				tmp = str;
				flag = 0;
			}
			else
			{
				if(str == tmp)
				{
					cout << "the repeat word is " << str << endl;
					findwor = 1;
				}
				else
					tmp = str;
			}

		}
		if(istr.eof() && findwor == 0)
			cout << "no repeat word" << endl;
	}


	return 0;
}
