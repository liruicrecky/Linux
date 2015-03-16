/*************************************************************************
	> File Name: ./src/word.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Mon 16 Mar 2015 03:36:47 PM CST
 ************************************************************************/

#include"word.h"

//class Word

void Word::initWordMap(std::ifstream *ifs)
{
	std::string line;
	std::string word;

	while(getline(ifs, line))
	{
		fileLine.push_back(line);
	}

	for(std::vector<std::string>::size_type lineno = 0;lineno != fileLine.size();++lineno)
	{
		std::istringstream istr(fileLine[lineno]);
		
		while(istr >> word)
		{
			wordMap[word].insert(lineno);
		}
	}
}
