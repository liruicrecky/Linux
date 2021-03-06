/*************************************************************************
	> File Name: ./src/func.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Sat 07 Mar 2015 10:06:25 PM CST
 ************************************************************************/

#include"wor.h"

//class

WOR::WOR() : word(""), cnt(0) {}

WOR::~WOR() {}

bool WOR::cmpWord(std::string &str) const 
{
	return word == str;
}

void WOR::setWord(std::string &str)
{
	word = str;
}

void WOR::setCnt(int x)
{
	cnt = x;
}

void WOR::addCnt()
{
	++cnt;
}

int WOR::getCnt() const
{
	return cnt;
}

std::string WOR::getWord() const
{
	return word;
}

//func

bool cmp(WOR a, WOR b)
{
	return a.getCnt() > b.getCnt();
}

void initFile(std::string &oriname, std::string &desname)
{
	std::string line;
	std::string str;
	size_t cnt;

	//open orifile and create new file
	
	std::ifstream ifs(oriname.c_str());
	std::ofstream ofs(desname.c_str());

	if(!ifs)
	{
		std::cout << "open file failed" << std::endl;
		return;
	}

	while(getline(ifs, line))
	{	
		for(cnt = 0;cnt != line.size();++cnt)
		{
			if(ispunct(line[cnt]))
				line[cnt] = ' ';
			if(isupper(line[cnt]))
				line[cnt] = tolower(line[cnt]);
		}

		ofs << line << std::endl;
	}

	ifs.close();
	ofs.close();
}
