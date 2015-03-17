/*************************************************************************
	> File Name: main.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Tue 17 Mar 2015 02:18:30 PM CST
 ************************************************************************/

#include"smart.h"

int main(void)
{
	int *kk = new int(500);

	SmartPtr sp1(kk, 500);
	SmartPtr sp2(sp1);
	SmartPtr sp3(sp2);
	SmartPtr sp4 = sp1;

	std::cout << sp1.getVal() << " " << sp1.getPtr() << std::endl
		      << sp2.getVal() << " " << sp2.getPtr() << std::endl
			  << sp3.getVal() << " " << sp3.getPtr() << std::endl
			  << sp4.getVal() << " " << sp4.getPtr() << std::endl;

	

	return 0;
}
