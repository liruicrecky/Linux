/*************************************************************************
	> File Name: ./src/thread/cache.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Wed 01 Apr 2015 03:07:32 PM CST
 ************************************************************************/

#include"Cache.h"

#include<fstream>
#include<utility>

CCache::CCache(const std::string &path) :
	_cache_path(path)
{
	readFromFile();
}

CCache::cacheMap::iterator CCache::isMapped(const std::string &str)
{
	cacheMap::iterator finder = _cache.find(str);
	return finder;
}

void CCache::addToCache(const std::string &ori, const std::string &fix)
{
	_cache.insert(std::pair<std::string, std::string>(ori, fix));
}

void CCache::writeToFile()
{
	std::ofstream ofs(_cache_path.c_str());

	std::tr1::unordered_map<std::string, std::string>::iterator it = _cache.begin();

	for(;it != _cache.end();++it){

		ofs << it -> first << " " << it -> second << std::endl;
	}

	ofs.close();
}

void CCache::readFromFile()
{
	std::ifstream ifs(_cache_path.c_str());

	std::string line;
	std::string::iterator siter;
	int pos;

	while(getline(ifs, line)){
	
		pos = line.find(' ');
		_cache.insert(std::pair<std::string, std::string>(line.substr(0, pos), line.substr(pos + 1)));
	}

	ifs.close();
}
