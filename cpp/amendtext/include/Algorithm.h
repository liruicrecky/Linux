/*************************************************************************
	> File Name: Algorithm.h
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Mon 30 Mar 2015 11:41:01 AM CST
 ************************************************************************/

#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include<stdlib.h>
#include<string>
#include<string.h>
#include<string.h>
#include"Conf.h"
#include<queue>
#include<iostream>
#include"SocketIO.h"

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
	return dArry[lenY - 1][lenX - 1];
}



void Task(int Fd, std::string &word, std::vector<std::pair<std::string, std::string> > &vecDict)
{
	std::vector<std::pair<std::string, std::string> >::const_iterator iter = vecDict.begin();

	//std::map<int, std::set<>
	std::queue<std::pair<std::string, std::string> > res;

	int minED = 10000;
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


	std::cout << minED << std::endl;

	char buf[1024];
	memset(buf, 0, 1024);

	for(size_t i = 0;i != res.size();++i)
	{
		std::string e = res.front().first;
		std::cout << e << std::endl;
		strcat(buf, e.c_str());
		res.pop();
	}

	SocketIO serIO;
	serIO.sendBuf(buf, Fd, 1024);
}


#endif
