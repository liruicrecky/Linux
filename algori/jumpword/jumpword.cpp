/*************************************************************************
	> File Name: jumpword.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Sat 07 Mar 2015 11:17:33 PM CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<cstring>

using std::cout;
using std::endl;
using std::string;

void reverStr(string &str)
{
	size_t strLen = str.size();
	size_t i, j;
	char tmp;

	i = 0;
	j = str.size() - 1;

	while(i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
}

void leftJump(string &str, int num)
{
	char left[10], right[10];

	size_t strLen = str.size();
	size_t leftLen = strLen - num;
	size_t i, j;

	if(num < leftLen)
	{
		for(i = 0, j = strLen - 1;i < num;i++, j--)
		{
			left[i] = str[i];
			right[i] = str[j];
		}

		left[i] = '\0';
		right[i] = '\0';

		cout << right << endl;

		string kk;
		strcpy(kk, right);
		
//		reverStr(left);
		reverStr(kk);

		for(i = 0, j = strLen - 1;i < num;i++, j--)
		{
			str[i] = right[i];
			str[j] = left[i];
		}
			
	//	reverStr(str);
	}
}

int main(void)
{
	string str = "abcdefg";
	int i = 2;

	cout << str << endl;

	leftJump(str, 2);

	cout << str << endl;
	
	return 0;
}

