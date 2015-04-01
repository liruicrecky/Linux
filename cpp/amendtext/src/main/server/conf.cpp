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
	_ifs.open(path.c_str());
	if(!_ifs)
	{
		std::cout << "open conf file failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	std::cout << "Open configfile successfully" << std::endl;

	//init wordMap
	
	initMap();
	initVecDict();
	indexToMap();

	//init socket
	
	initAddr();
	
}

CConf::~CConf()
{
	_ifs.close();
}

void CConf::initMap()
{
	unsigned int pos;
	std::string line, key, value;
	while(getline(_ifs, line))
	{
		pos = line.find('=');
		if(std::string::npos == pos)
			continue;
		_map.insert(std::pair<std::string, std::string>(line.substr(0, pos), line.substr(pos + 1)));
	}

/*
	for(std::map<std::string, std::string>::iterator iter = _map.begin();iter != _map.end();++iter)
	{
		std::cout << iter -> first << " " << iter -> second << std::endl;
	}
*/
}

void CConf::initVecDict()
{
	//find word_map path and open the file
	std::map<std::string, std::string>::iterator it = _map.find("Word_map");
	std::ifstream ifs((it -> second).c_str());
	if(!ifs)
	{
		perror("Open word file failed!");
		exit(EXIT_FAILURE);
	}

	//find the ' ' to get key(word) and value(freque)
	//put into vector<pair<string, string> >
	int pos;
	std::string line, word, freque;
	std::pair<std::string, std::string> pairWord;

	while(getline(ifs, line))
	{
		pos = line.find(' ');
		_vecDict.push_back(make_pair(line.substr(0, pos), line.substr(pos + 1)));
	}
/*
	for(std::vector<std::pair<std::string, std::string> >::iterator iter = _vecDict.begin();iter != _vecDict.end();++iter)
	{
		std::cout << iter -> first << " "  << iter -> second << std::endl;
	}
*/

	ifs.close();
}

void CConf::indexToMap()
{
	std::vector<std::pair<std::string, std::string> >::size_type ix = 0;
	std::string::size_type iy = 0;
	
	for(;ix != _vecDict.size();++ix)
	{
	//	for(iy = 0;iy != _vecDict[ix].first.size();++iy)
//		{
			std::string substr(_vecDict[ix].first.substr(0, 1));
			_indexVect[substr].insert(ix);
	//	}
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


void CConf::initAddr()
{
	std::map<std::string, std::string>::iterator ip, port, mode;
			
	ip = _map.find("Ip");
	port = _map.find("Port");
	mode = _map.find("Mode");

	_ip = ip -> second;
	_port = atoi((port -> second).c_str());
	_mode = mode -> second;
}


