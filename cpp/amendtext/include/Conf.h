/*************************************************************************
	> File Name: include/conf.h
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Wed 25 Mar 2015 09:25:38 PM CST
 ************************************************************************/

#ifndef __CONF_H__
#define __CONF_H__

#include<boost/noncopyable.hpp>
#include<string>
#include<fstream>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<tr1/unordered_map>

class CConf : boost::noncopyable
{

	typedef std::vector<std::pair<std::string, std::string> > VECDICT;
	typedef std::map<std::string, std::string> MAP;
	typedef std::tr1::unordered_map<std::string, std::set<int> > INDEXVECT;
	
private:

	std::string ip;
	int port;

	VECDICT _vecDict;
	MAP _map;
	INDEXVECT _indexVect;
//	std::map<std::string, std::set<int> > _indexVect;
	std::ifstream _ifs;

	int _threadNum;
	int _queueSize;

	void initMap();
	void initVecDict();


	void initData(); // socket, thread

private: //socket

	std::string _ip;
	std::string _mode;
	int _port;

private: 

public:  //init
	
	CConf() { }
	~CConf();
	explicit CConf(const std::string &);
	void indexToMap();

	
public:  //socket

	std::string Ip() {return _ip; }
	std::string Mode() {return _mode; }
	int Port() {return _port; }

public: //thread

	int ThreadNum() {return _threadNum; }
	int QueueSize() {return _queueSize; }

public: //return map

	VECDICT *getVecDict() {return &_vecDict; }
	INDEXVECT *getIndexDict(){return &_indexVect; }

};

#endif
