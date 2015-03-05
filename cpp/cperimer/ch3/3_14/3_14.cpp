/*************************************************************************
	> File Name: 3_14.cpp
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Thu 05 Mar 2015 10:30:12 PM CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<vector>
#include<cctype>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(int argc, char **argv)
{
	vector<string> word;
	string str;

	while(cin >> str)
		word.push_back(str);

	for(vector<string>::iterator iter = word.begin();iter != word.end();++iter)
	{
		for(int i = 0;i != (*iter).size();i++)
		{
			if(islower((*iter)[i]))
				(*iter)[i] = toupper((*iter)[i]);
		}
		
		cout << *iter << endl;
	}

//	cout << endl;

	return 0;
}

