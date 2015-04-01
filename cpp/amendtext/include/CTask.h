/*************************************************************************
	> File Name: /home/liruicheng/LinuxCode/cpp/amendtext/include/CTask.h
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Mon 30 Mar 2015 08:28:18 PM CST
 ************************************************************************/

#ifndef __CTASK_H__
#define __CTASK_H__

#include<string>
#include<vector>
#include<utility>
#include<queue>
#include<netinet/in.h>
#include<tr1/unordered_map>

#include"Conf.h"

class CResult
{
public:
	std::string _word;
	int _eDict;
	int _wFrequence;
};

class CCompare
{
public:
	
	bool operator()(const CResult &lhs, const CResult &rhs)
	{ return lhs._eDict > rhs._eDict; }
};

class CTask
{
private:

	std::string _word;
	struct sockaddr_in _addr;
	int _fd;

	std::vector<std::pair<std::string, std::string> > *_vecDict;
	std::tr1::unordered_map<std::string, std::set<int> > *_indexDict;
	std::priority_queue<CResult, std::vector<CResult>, CCompare> _result;

public:

	CTask(CConf &, const char*, int);

public:

	void satistic(const std::set<int> &);
	int editDistance(const std::string &);
	void execute();

public:

	void setWord(const char* buf) {_word = buf; }
	void setFd(int fd) {_fd = fd; }
	void setSockAddr(struct sockaddr_in &);

};

#endif

