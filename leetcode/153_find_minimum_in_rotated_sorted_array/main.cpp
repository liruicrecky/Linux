/*************************************************************************
	> File Name: main.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Wed 18 Mar 2015 08:52:44 PM CST
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

int findMin(vector<int> &num)
{
	int min = num[0];
	for(vector<int>::iterator iter = num.begin();iter != num.end();++iter){

		if(min > *iter){
			min = *iter;
		}
	}

	return min;
}

int findMin1(vector<int> &num)
{
	int str, end, mid;
	str = 0;
	end = num.size();

	int min = num[0];

	while(str < end){

		mid = (str + end) >> 1;

		if(str == mid)
			break;
		else if(min > num[mid]){
			if(num[mid] < min)
				min = num[mid];
			end = mid - 1;
		}else if(num[mid] >= min){
			if(num[str] < min)
				min = num[str];
			str = mid + 1;
		}

	}

	if(num[str] < min){
		min = num[str];
	}else if(num[end] < min){
		min = num[end];
	}

	return min;
}
