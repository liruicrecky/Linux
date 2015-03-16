/*************************************************************************
  > File Name: ./word.h
  > Author: Reacky
  > Mail:327763224@qq.com 
  > Created Time: Fri 13 Mar 2015 08:28:41 PM CST
 ************************************************************************/

#ifndef __WORD_H__
#define __WORD_H__

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<fstream>
#include<stdexcept>

class fileHandle
{
	public:
		fileHandle() {}
		~fileHandle()
		{
			ifs.close();
		}
		void openFile(const std::string &s)
		{
			ifs.open(s.c_str());
			if(!ifs)
				throw std::runtime_error("Open file error!");
			else
				std::cout << "Open file successed!" << std::endl;
		}
		std::ifstream &getIfs()
		{
			return ifs;
		}
	private:
		std::ifstream ifs;
		fileHandle(const fileHandle &);
		fileHandle &operator=(const fileHandle &);
};

class WORD
{
	public:
		typedef std::set<std::vector<std::string>::size_type> setype;
	private:
		void saveFileLine(std::ifstream &);
		void initWordMap();

		std::vector<std::string> fileLine;
		std::map< std::string, setype > wordMap;

	public:
		void openFile(std::ifstream &);
		setype findWord(const std::string &) const;
		std::string getLineText(setype::size_type) const;
};

void print(const WORD::setype &res, const std::string &inputword, const WORD word);



#endif

