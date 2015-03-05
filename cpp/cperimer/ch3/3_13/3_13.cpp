/*************************************************************************
	> File Name: 3_13.cpp
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Thu 05 Mar 2015 09:59:39 PM CST
 ************************************************************************/

#include<iostream>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main(int argc, char **argv)
{
	int x;
	vector<int> ivec;

	while(cin >> x)
		ivec.push_back(x);

	bool isodd;

	if(ivec.size() % 2 != 0)
		isodd = 1;
	else 
		isodd = 0;

	for(vector<int>::iterator iter = ivec.begin();iter != ivec.end();iter += 2)
	{
		if(isodd && iter == ivec.end() - 1)
			break;

		cout << "The two near num is:" << *iter << " " << *(iter + 1) << " "					  << "the sum is:" << *(iter) + *(iter + 1) << endl;
	}

	if(isodd)
		cout << "The size of the vector is odd, the last num is:" << ivec[ivec.size() - 1] << endl;

	return 0;
}
