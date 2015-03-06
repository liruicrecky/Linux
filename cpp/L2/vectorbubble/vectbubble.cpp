/*************************************************************************
	> File Name: vectbubble.cpp
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Thu 05 Mar 2015 07:29:08 PM CST
 ************************************************************************/

#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<vector>
#include<algorithm>


void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

int main(int argc, char **arrv)
{
	std::vector<int> ivec(20);
	std::vector<int> ivec1(20);

	srand(time(NULL));

	for(std::vector<int>::iterator ix = ivec.begin();ix != ivec.end();ix++)
	{
		*ix = rand() % 1000 + 1;
		std::cout<<*ix<<" ";
	}

	std::cout<<std::endl;

	//bubble
	
	int i, j;

	for(i = 0;i < ivec.size();i++)
	{
		for(j = i; j < ivec.size();j++)
		{
			if(ivec[j] < ivec[i])
				swap(ivec[i], ivec[j]);
		}
	}

	for(std::vector<int>::iterator ix = ivec.begin();ix != ivec.end();ix++)
		std::cout<<*ix<<" ";

	std::cout<<std::endl;

	//sort
	
	for(std::vector<int>::iterator ix = ivec1.begin();ix != ivec1.end();ix++)
	{
		*ix = rand() % 1000 + 1;
		std::cout<<*ix<<" ";
	}

	std::cout<<std::endl;
	
	sort(ivec1.begin(), ivec1.end());

	for(std::vector<int>::iterator ix = ivec1.begin();ix != ivec1.end();ix++)
		std::cout<<*ix<<" ";

	std::cout<<std::endl;

	return 0;
}
