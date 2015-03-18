/*************************************************************************
  > File Name: mian.cpp
  > Author: Reacky
  > Mail:327763224@qq.com 
  > Created Time: Wed 18 Mar 2015 04:58:29 PM CST
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

int minimumTotal(vector<vector<int> > &triangle) {
	int i, j;
	i = triangle.size() - 2;

	for(;i != -1;--i){
		for(j = 0; j != i + 1;++j){
			if(triangle[i + 1][j] > triangle[i + 1][j + 1]){
				triangle[i][j] += triangle[i + 1][j + 1];
			}else{
				triangle[i][j] += triangle[i + 1][j];
			}
		}
	}

	return triangle[0][0];
}

int main(void)
{
	vector<vector<int> > vec;
	vector<int> ele;

	ele.push_back(1);
	vec.push_back(ele);
	ele.clear();
	ele.push_back(2);
	ele.push_back(3);
	vec.push_back(ele);
//	ele.clear();
//	ele.push_back(1);
//	ele.push_back(-1);
//	ele.push_back(-3);
//	vec.push_back(ele);
	
	cout << minimumTotal(vec) << endl;

	return 0;
}
