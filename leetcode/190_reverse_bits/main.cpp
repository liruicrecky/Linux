/*************************************************************************
	> File Name: main.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Thu 12 Mar 2015 05:16:36 PM CST
 ************************************************************************/

#include<iostream>
#include<stdint.h>
#include<math.h>
#include<time.h>

int main(void)
{
	uint32_t n = 1;
	time_t str, end;

	std::cout << "n: " << n << std::endl;
	
	int arr[32] = { 0 };
	int i = -1;
	str = clock();
	while(n){
		arr[++i] = n % 2;
		n /= 2;
	}
	uint32_t k = 0;
	i = -1;
	int j = 32;
	while(i != 32){
		k += pow(2, --j) * arr[++i];
	}
	
	end = clock();

	std::cout << "n: " << k << std::endl;
	std::cout << "time: " << (static_cast<double>(end - str) / CLOCKS_PER_SEC) << std::endl;

	return 0;
}
