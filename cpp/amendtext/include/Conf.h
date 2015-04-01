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
private:

	std::string ip;
	int port;

	std::vector<std::pair<std::string, std::string> > _vecDict;
	std::map<std::string, std::string> _map;
	std::tr1::unordered_map<std::string, std::set<int> > _indexVect;
//	std::map<std::string, std::set<int> > _indexVect;
	std::ifstream _ifs;

	void initMap();
	void initVecDict();

private: //socket

	std::string _ip;
	std::string _mode;
	int _port;

	void initAddr();

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


public: //return map

	std::vector<std::pair<std::string, std::string> > *getVecDict() {return &_vecDict; }

	std::tr1::unordered_map<std::string, std::set<int> > *getIndexDict(){return &_indexVect; }

};

#endif
