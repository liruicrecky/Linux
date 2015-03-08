/*************************************************************************
	> File Name: 6_18.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Sun 08 Mar 2015 10:34:52 PM CST
 ************************************************************************/

#include<iostream>
#include<string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(void)
{
	string rep;

	do
	{
		string str1;
		string str2;

		cout << "input two strings :";
		cin >> str1 >> str2;

		size_t min, i;

		min = str1.size() > str2.size() ? str2.size() : str1.size();

		for(i = 0;i != min;++i)
		{
			if(str1[i] > str2[i])
			{
				cout << "The str '" << str2 << "' is low" << endl;
				break;
			}
			else if(str1[i] < str2[i])
			{
				cout << "The str '" << str1 << "' is low" << endl;
				break;
			}
		}

		if(i == min)
		{
			if(str1.size() == min && str2.size() == min)
				cout << "The two strings are the same" << endl;
			else if(str1.size() == min)
				cout << "The str '" << str2 << "' is low" << endl;
			else
				cout << "The str '" << str1 << "' is low" << endl;
		}

		cout << "continue?(y/n)";
		cin >> rep;

	}while(!rep.empty() && rep[0] != 'n');

	return 0;
}
