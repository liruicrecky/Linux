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

#define MININTHREE(x, y, z) \
	((x) > ((y) > (z) ? (z) : (y)) ? ((y) > (z) ? (z) : (y)) : (x))


CTask::CTask(CConf &conf, const char *buf, int fd, CCache &cache) :
	_word(buf),
	_fd(fd),
	_vecDict(conf.getVecDict()),
	_indexDict(conf.getIndexDict()),
	_cache(cache) { }

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

	for(i = 1;i != lenY;++i){

		for(j = 1;j != lenX;++j){

			if(_word[i - 1] == X[j - 1])
				lefttop = dArry[i - 1][j - 1];
			else
				lefttop = dArry[i - 1][j - 1] + 1;

			left = dArry[i][j - 1] + 1;
			top = dArry[i - 1][j] + 1;

			dArry[i][j] = MININTHREE(left, top, lefttop);
		}
	}

	return dArry[lenY - 1][lenX - 1];
}

void CTask::satistic(const std::set<int> &wSet)
{
	CResult res;

	std::set<int>::const_iterator it = wSet.begin();

	for(;it != wSet.end();++it){

		res._word = (*_vecDict)[*it].first;
		res._eDict = editDistance((*_vecDict)[*it].first);
		res._wFrequence = atoi((*_vecDict)[*it].second.c_str());

		_result.push(res);
	}

}


void CTask::execute()
{
	char buf[1024];

	INDEXDICT::const_iterator indexIter;

	std::tr1::unordered_map<std::string, std::string, CHasFn>::iterator res;

	if((*(_cache.getHashMap())).end() != (res = _cache.isMapped(_word))){

		memset(buf, 0, sizeof(buf));
		strcpy(buf, (res -> second).c_str());
		write(_fd, buf, sizeof(buf));

	}else{

		for(std::string::size_type it = 0;it != _word.size();++it){

			std::string str(_word, it, 1);
			indexIter = (*_indexDict).find(str);
			satistic(indexIter -> second);
		}


		memset(buf, 0, sizeof(buf));
		if(_result.empty()){

			strcpy(buf, "no result");
			write(_fd, buf, sizeof(buf));

		}else{

			sprintf(buf, "%s %d", _result.top()._word.c_str(), _result.top()._eDict);
			write(_fd, buf, sizeof(buf));
			_cache.addToCache(_word, _result.top()._word);
		}
	}

}



