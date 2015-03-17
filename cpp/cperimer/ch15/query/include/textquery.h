/*************************************************************************
	> File Name: ./include/textquery.h
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Mon 16 Mar 2015 03:25:49 PM CST
 ************************************************************************/

#ifndef __TEXTQUERY_H__
#define __TEXTQUERY_H__

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

class TextQuery
{
public:
	typedef std::vector<std::string>::size_type line_no;

	void initFile(std::ifstream &);
	std::set<line_no> exQuery(const std::string &) const;
	std::string getTextLine(line_no) const;
	line_no size() const;
private:
	std::map<std::string, std::set<line_no> > wordMap;
	std::vector<std::string> fileLine;
	void initWordMap(std::ifstream &);
};

#endif
