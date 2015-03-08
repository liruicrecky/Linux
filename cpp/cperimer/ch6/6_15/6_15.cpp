/*************************************************************************
	> File Name: 6_15.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Sun 08 Mar 2015 10:15:15 PM CST
 ************************************************************************/

#include<iostream>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

bool cmpVect(vector<int> &a, vector<int> &b)
{
	vector<int>::size_type aLen, bLen;

	aLen = a.size();
	bLen = b.size();

	vector<int>::iterator itera = a.begin();
	vector<int>::iterator iterb = b.begin();

	if(aLen == bLen)
	{
		for(;itera != a.end();++itera, ++iterb)
		{
			if(*itera != *iterb)
				return 0;
		}
		
		return 1;
	}
	else if(aLen > bLen)
	{
		for(;iterb != b.end();++itera, ++iterb)
		{
			if(*itera != *iterb)
				return 0;
		}
		
		return 1;
	}
	else
	{
		for(;itera != a.end();++itera, ++iterb)
		{
			if(*itera != *iterb)
				return 0;
		}
		
		return 1;
	}
}

int main(void)
{
	vector<int> ivect1;
	vector<int> ivect2;

	size_t i;

	for(i = 0;i < 3;++i)
	{
		ivect1.push_back(i);
	}

	for(i = 0;i < 7;++i)
	{
		ivect2.push_back(i * 2);
	}

	if(cmpVect(ivect1, ivect2))
		cout << "ture" << endl;
	else
		cout << "false" << endl;

	return 0;
}
