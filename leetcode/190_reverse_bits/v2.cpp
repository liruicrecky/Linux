/*************************************************************************
	> File Name: v2.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Thu 12 Mar 2015 07:45:43 PM CST
 ************************************************************************/

#include<iostream>
#include<stdint.h>
#include<time.h>

uint32_t reverse(uint32_t n)
{
	int i = 33;
	uint32_t k = 0;

	while(--i)
	{
		k <<= 1;
		k |= n & 1;
		n >>= 1;
	}

	return k;
}

int main(void)
{
	uint32_t n = 1;
	time_t str, end;

	str = clock();

	std::cout << "n: " << n << std::endl
		      << "n: " << reverse(n) << std::endl;

	end = clock();

	std::cout << "time: " << (static_cast<double>(end - str) / CLOCKS_PER_SEC) << std::endl;

	return 0;
}
