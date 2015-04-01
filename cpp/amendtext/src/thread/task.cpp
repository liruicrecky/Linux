/*************************************************************************
	> File Name: /home/liruicheng/LinuxCode/cpp/amendtext/src/task/src/task.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Mon 30 Mar 2015 08:41:54 PM CST
 ************************************************************************/

#include"CTask.h"

#include<iostream>
#include<string.h>
#include<stdlib.h>

CTask::CTask(CConf &conf, std::string buf, int fd) :
	_word(buf),
	_fd(fd),
	_vecDict(conf.getVecDict()),
	_indexDict(conf.getIndexDict()) { }

int minInThree(int a, int b, int c)
{
	int tmp = a > b ? b : a;
	return tmp > c ? c : tmp;
}

int CTask::editDistance(const std::string &X)
{
	//cal length
	int lenX = X.size() + 1;
	int lenY = _word.size() + 1;

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
			if(_word[i - 1] == X[j - 1])
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

void CTask::satistic(const std::set<int> &wSet)
{
	CResult res;

	std::set<int>::const_iterator it = wSet.begin();

	for(;it != wSet.end();++it)
	{
		res._word = (*_vecDict)[*it].first;
		res._eDict = editDistance((*_vecDict)[*it].first);
		res._wFrequence = atoi((*_vecDict)[*it].second.c_str());
		
		_result.push(res);
	}

}


void CTask::execute()
{
	char buf[1024];

	std::string::iterator it = _word.begin();
	std::tr1::unordered_map<std::string, std::set<int> >::const_iterator indexIter;

	std::set<int>::const_iterator miter;

	for(;it != _word.end() - 1;++it)
	{
		char s[1];
		s[0] = *it;
		std::string str(s);
		indexIter = (*_indexDict).find(str);
//		std::cout << indexIter -> first << std::endl;
	//	for(miter = (indexIter -> second).begin();miter != (indexIter -> second).end();++miter)
	//	{
	//		std::cout << *miter << " ";
	//	}
		satistic(indexIter -> second);
	}

	
	memset(buf, 0, sizeof(buf));
	if(_result.empty())
	{
		strcpy(buf, "no result");
		write(_fd, buf, sizeof(buf));
	}
	else
	{
		sprintf(buf, "%s %d", _result.top()._word.c_str(), _result.top()._eDict);
		write(_fd, buf, sizeof(buf));
	}
	
}



