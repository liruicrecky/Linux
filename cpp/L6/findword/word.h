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

//文件raii
class fileHandle
{
	public:
		//构造函数
		fileHandle() { };
		fileHandle(const std::string &s)
		{
			ifs.open(s.c_str());
		}
		//析构函数，释放使用资源
		~fileHandle()
		{
			ifs.close();
		}
		//打开文件，也可以直接用构造函数
		void openFile(const std::string &s)
		{
			//打开文件
			ifs.open(s.c_str());
			//如果打开失败，抛出错误，否则打开成功
			if(!ifs)
				throw std::runtime_error("Open file error!");
			else
				std::cout << "Open file successed!" << std::endl;
		}
		//获取私有变量ifs
		std::ifstream &getIfs()
		{
			return ifs;
		}
	private:
		//文件操作符
		std::ifstream ifs;
		//复制构造函数和赋值函数对文件类型禁止使用
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

