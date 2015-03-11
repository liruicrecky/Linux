/*************************************************************************
	> File Name: mian.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Wed 11 Mar 2015 10:37:44 PM CST
 ************************************************************************/

#include<iostream>

using std::cout;
using std::endl;

void *cal(int *input, int n)
{
	int *res = new int[n];
	int i;

	res[0] = 1;
	for(i = 1;i < n;++i)
		res[i] = res[i - 1] * input[i - 1];
	res[0] = input[n - 1];
	for(i = n - 2;i > 0;--i)
	{
		res[i] *= res[0];
		res[0] *= input[i];
	}
	for(i = 0; i != n;++i)
		cout << res[i] << endl;
	delete res;
	res = NULL;
}

int main(void)
{
	int a[] = {1,2,3,4,5,6,7,8};
	cal(a, 8);


	return 0;
}
