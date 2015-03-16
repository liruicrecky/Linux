/*************************************************************************
	> File Name: ./include/word.h
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Mon 16 Mar 2015 03:25:49 PM CST
 ************************************************************************/

#ifndef __WORD_H__
#define __WORD_H__

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<stdexcept>
#include<map>
#include<set>

class fileHandle
{
public:
	fileHandle() { }
	~fileHandle()
	{
		ifs.close();
	}

	void open(std::string &s)
	{
		ifs.open(s.c_str());
		if(!ifs)
			throw std::runtime_error("Open file failed");
		else
			std::cout << "Open file successed";
	}

	std::ifstream &getIfs()
	{
		return ifs;
	}

private:
	fileHandle(const fileHandle &);
	fileHandle &operator=(const fileHandle &);
	std::ifstream ifs;

};

class Word
{
public:
	typedef std::set<std::vector<std::string>::size_type> lineNo;

	void initFile(std::ifstream &);
private:
	std::map<std::string, lineNo> wordMap;
	std::vector<std::string> fileLine;
	void initWordMap(std::ifstream &);
};



#endif
