/*************************************************************************
	> File Name: ./src/wor.h
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Sat 07 Mar 2015 09:57:51 PM CST
 ************************************************************************/

#ifndef __WOR_H__
#define __WOR_H__

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<ctime>

class WOR
{
public:
	WOR();
	~WOR();
	void setWord(std::string &str);
	void setCnt(int x);
	void addCnt();
	bool cmpWord(std::string &str) const;
	int getCnt() const;
	std::string getWord() const;

private:
	std::string word;
	int cnt;
};


void initFile(std::string &oriname, std::string &desname);
bool cmp(WOR a, WOR b);


#endif
