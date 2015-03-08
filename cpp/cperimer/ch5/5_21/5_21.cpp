/*************************************************************************
	> File Name: 5_21.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Sun 08 Mar 2015 09:11:35 PM CST
 ************************************************************************/

#include<iostream>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main(void)
{
	int x;
	vector<int> ivec;

	while(cin >> x && !cin.eof())
	{
		if(x < 0)
		{
			cout << "value should be positive" << endl;
			continue;
		}

		ivec.push_back(x);
	}

	vector<int>::iterator iter = ivec.begin();

	cout << "The vals are: ";
	for(;iter != ivec.end();++iter)
	{
		cout << *iter << " ";
		if(*iter % 2 != 0)
			*iter *= 2;
	}

	cout << endl;

	iter = ivec.begin();

	cout << "The new vals are: ";
	for(;iter != ivec.end();++iter)
		cout << *iter << " ";

	cout << endl;

	return 0;
}
