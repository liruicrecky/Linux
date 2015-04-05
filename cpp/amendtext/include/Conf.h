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

	/* sock data */
	std::string _ip;
	std::string _mode;
	int _port;

	/* dict data */

	VECDICT _vecDict;
	MAP _map;
	INDEXVECT _indexVect;

	std::ifstream _ifs;

	/* thread data */

	int _threadNum;
	int _queueSize;

	/* cache data */

	std::string _cache_path;

	std::string _redis_ip;
	int _redis_port;

	/* init function */

	void initMap();
	void initVecDict(std::string &);
	void indexToMap();
	void initData();

public:  

	/* init class */

	CConf() { }
	~CConf();
	explicit CConf(const std::string &);

	
public:  

	/* socket interface */

	std::string Ip() {return _ip; }
	std::string Mode() {return _mode; }
	int Port() {return _port; }

public: 

	/* thread interface */

	int ThreadNum() {return _threadNum; }
	int QueueSize() {return _queueSize; }

public: 

	/* map interface */

	VECDICT *getVecDict() {return &_vecDict; }
	INDEXVECT *getIndexDict(){return &_indexVect; }

public:

	/* cache interface */

	std::string getCachePath() {return _cache_path; }

	/* redis interface */

	std::string getRedisIp() {return _redis_ip; }
	int getRedisPort() {return _redis_port; }

};

#endif
