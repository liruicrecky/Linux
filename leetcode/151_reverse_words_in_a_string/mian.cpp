/*************************************************************************
	> File Name: mian.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Wed 11 Mar 2015 03:02:16 PM CST
 ************************************************************************/

#include<iostream>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

//init string

void initString(string &s)
{
	string::iterator siter;

	siter = s.begin();
	
	//del first ' '
	
	while(*siter == ' ')
		s.erase(siter);

	//del middld
	
	while(siter != s.end())
	{
		if(*(siter) == ' ' && *(siter + 1) == ' ')
		{
			s.erase(siter + 1);
			continue;
		}
	
		++siter;
	}

	//end
	
	if(*(siter - 1) == ' ')
		s.erase(siter - 1);

}

//reverse word

void reverseString(string &s, string::size_type &beg, string::size_type &end)
{
	char tmp;
	while(beg < end)
	{
		tmp = s[beg];
		s[beg] = s[end];
		s[end] = tmp;
		++beg;
		--end;
	}
}

int main(void)
{
	string str;

	cout << "input a string: ";
	getline(cin, str);

	cout << str << endl;

	initString(str);

	cout << str << endl;

	if(!str.size())
	{
		cout << "no word" << endl;
		return 0;
	}

	//reverse every word
	
	string::size_type i = 0, j;
	string::size_type tmpi, tmpj;

	while((i = str.find_first_not_of(' ', i)) != string::npos)
	{
		j = str.find_first_of(' ', i);

		if(j == string::npos)
			j = str.size();

		tmpi = i;
		i = j;
		tmpj = --j;
	
		reverseString(str, tmpi, tmpj);
	}

	//reverse string

	i = 0;
	j = str.size() - 1;

	reverseString(str, i, j);

	cout << str << endl;
	
	return 0;
}
