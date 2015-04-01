/*************************************************************************
	> File Name: eDistance.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Sun 29 Mar 2015 09:23:46 PM CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<string.h>



int minInThree(int a, int b, int c)
{
	int tmp = a > b ? b : a;
	return tmp > c ? c : tmp;
}

int EditDistanceDP(std::string X, std::string Y)
{
	//cal length
	int lenX = X.size() + 1;
	int lenY = Y.size() + 1;

	//new d-array
	
	int dArry[lenY][lenX];
	memset(dArry, 0, sizeof(int) * lenX * lenY);

	int i, j;
	int left, top, lefttop;

	for(j = 1;j != lenX;++j)
		dArry[0][j] = j;

	for(i = 1;i != lenY;++i)
		dArry[i][0] = i;

	for(i = 1;i != lenY;++i)
	{
		for(j = 1;j != lenX;++j)
		{
			if(Y[i - 1] == X[j - 1])
				lefttop = dArry[i - 1][j - 1];
			else
				lefttop = dArry[i - 1][j - 1] + 1;

			left = dArry[i][j - 1] + 1;
			top = dArry[i - 1][j] + 1;

			dArry[i][j] = minInThree(left, top, lefttop);
		}
	}

 // test code
 //

	int k = -1;
	std::cout << "    ";
	for(std::string::iterator iter = X.begin();iter != X.end();++iter)
	{
		std::cout << *iter << " ";
	}

	std::cout << std::endl;
	for(i = 0;i != lenY;++i)
	{
		for(j = 0;j != lenX;++j)
		{
			if(j == 0 && i != 0)
				std::cout << Y[++k] << " ";
			else if(j == 0 && i == 0)
				std::cout << "  ";
			std::cout << dArry[i][j] << " ";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
    

	return dArry[lenY - 1][lenX - 1];
}

//test code



int main(int argc, char **argv)
{
//	std::cout << minInThree(atoi(argv[1]), atoi(argv[2]), atoi(argv[3])) << std::endl;

	std::string x("apple");
	std::string y("applr");

	int res = EditDistanceDP(x, y);

	std::cout << res << std::endl;
	return 0;
}



/*

void Task(int Fd, std::string &word, std::vector<std::pair<std::string, std::string> > &vecDict)
{
	std::vector<std::pair<std::string, std::string> >::const_iterator iter = vecDict.begin();

	//std::map<int, std::set<>
	std::queue<std::map<std::string, std::string> > res;

	int minED = -1;
	for(;iter != vecDict.end();++iter)
	{
		if(minED > EditDistanceDP(word, iter -> first))
			minED = EditDistanceDP(word, iter -> first);
	}

	iter = vecDict.begin();
	for(;iter != vecDict.end();++iter)
	{
		if(minED == EditDistanceDP(word, iter -> first))
			res.push(std::pair<std::string, std::string>(iter -> first, iter -> second));
	}

	for(size_t i = 0;i != res.size();++i)
	{
		std::string e = res.front();
		std::cout << e << std::endl;
		res.pop();
	}

}
*/

