/*************************************************************************
	> File Name: ./src/conf.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Wed 25 Mar 2015 09:36:25 PM CST
 ************************************************************************/

#include"Conf.h"
#include<iostream>
#include<stdlib.h>

CConf::CConf(const std::string &path)
{
	/* open config file */

	_ifs.open(path.c_str());
	if(!_ifs){

		std::cout << "open conf file failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	std::cout << std::endl << "Init server, processing..." << std::endl
		      <<"/-----Open config file success-----" << std::endl;

	/* init dict */
	
	initMap();

	/*
	 *  init cn and en dict
	 */ 

	MAP::iterator it;

	it = _map.find("Word_map_en");
	initVecDict(it -> second);

	it = _map.find("Word_map_cn");
	initVecDict(it -> second);


	indexToMap();

	/* init data */
	
	initData();
	
}

CConf::~CConf()
{
	_ifs.close();
}

void CConf::initMap()
{
	unsigned int pos;
	std::string line;
	while(getline(_ifs, line)){

		pos = line.find('=');
		if(std::string::npos == pos)
			continue;

		_map.insert(std::pair<std::string, std::string>(line.substr(0, pos), line.substr(pos + 1)));
	}
}

void CConf::initVecDict(std::string &path)
{
	/*
	 * find word_map path and open the file
	 */

	std::ifstream ifs(path.c_str());

	if(!ifs){

		perror("Open word file failed!");
		exit(EXIT_FAILURE);
	}

	/*
	 *  find char ' ' to get key(word) and value(freque)
	 *  and put them into vector<pair<string, string> >
	 */

	int pos;
	std::string line;
	std::pair<std::string, std::string> pairWord;

	while(getline(ifs, line)){

		pos = line.find(' ');
		_vecDict.push_back(make_pair(line.substr(0, pos), line.substr(pos + 1)));
	}

	ifs.close();
}

void CConf::indexToMap()
{
	VECDICT::size_type ix = 0;

	for(;ix != _vecDict.size();++ix){

		if(_vecDict[ix].first[0] & (1 << 7))
		{
			std::string substr(_vecDict[ix].first.substr(0, 3));
			_indexVect[substr].insert(ix);

		}else{

			std::string substr(_vecDict[ix].first.substr(0, 1));
			_indexVect[substr].insert(ix);
		}
	}
/*

	std::tr1::unordered_map<std::string, std::set<int> >::const_iterator iter = _indexVect.begin();
	std::set<int>::const_iterator siter;
	for(;iter != _indexVect.end();++iter)
	{
		std::cout << iter -> first << " ";
		for(siter = (iter -> second).begin();siter != (iter -> second).end();++siter)
		{
			std::cout << *siter << " ";
		}
		std::cout << std::endl;
	}
*/
	
}


void CConf::initData()
{
	MAP::iterator finder;

	/*
	 *  socket data
	 */

	finder = _map.find("Ip");
	_ip = finder -> second;

	finder = _map.find("Port");
	_port = atoi((finder -> second).c_str());

	finder = _map.find("Mode");
	_mode = finder -> second;

	/*
	 *  thread data
	 */

	finder = _map.find("ThreadNum");
	_threadNum = atoi((finder -> second).c_str());

	finder = _map.find("QueueSize");
	_queueSize = atoi((finder -> second).c_str());

	/*
	 *  cache data
	 */

	finder = _map.find("CachePath");
	_cache_path = finder -> second;

	/*
	 *  redis data
	 */

	finder = _map.find("Redis_IP");
	_redis_ip = finder -> second;

	finder = _map.find("Redis_PORT");
	_redis_port = atoi((finder -> second).c_str());
}


