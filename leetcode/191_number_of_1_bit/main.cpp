/*************************************************************************
	> File Name: main.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Wed 11 Mar 2015 10:34:59 AM CST
 ************************************************************************/

#include<iostream>
#include<stdint.h>

using std::cout;
using std::endl;

int count1(uint32_t n)
{
	int cnt = 0;
	while(n)
	{
		n &= n - 1;
		++cnt;
	}

	return cnt;
}

int count2(uint32_t n)
{
	int cnt = 0;
	for(int  i = 0;i < 32;++i)
	{
		if(n & 0x0001)
			++cnt;
		n = n >> 1;
	}
	
	return cnt;
}

int main(void)
{
	uint32_t n = 0x7a4f;

	uint32_t tmp = n;
	
	cout << count1(n) << endl;
	cout << count2(tmp) << endl;

	return 0;
}
