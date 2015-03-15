/*************************************************************************
	> File Name: ./include/msg.h
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Sat 14 Mar 2015 10:11:29 PM CST
 ************************************************************************/

#ifndef __MSG_H__
#define __MSG_H__

#include<iostream>
#include<string>
#include<ifstream>
#include<vector>
#include<map>
#include<set>

class MSG
{
public:

	typedef std::set<std::vector<std::string>::size_type> lineNum;

	MSG();
	void print(const std::string &);
	void showMsg(const std::map<std::string, lineNum> &);



private:
	
	void initFile(std::ifstream &)
	void initMap(std::vector<std::string> &)
	std::map<std::string, lineNum> wordMap;
	std::vector<string> file;

};


#endif


