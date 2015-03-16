/*************************************************************************
	> File Name: ./func.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Fri 13 Mar 2015 08:28:30 PM CST
 ************************************************************************/

#include"word.h"
#include<sstream>

//class

void WORD::saveFileLine(std::ifstream &ifs)
{
	std::string line;
	while(getline(ifs, line))
	{
		/*
		for(std::string::iterator iter = line.begin();iter != line.end();++iter)
		{
			if(ispunct(*iter))
				*iter = ' ';
			if(isupper(*iter))
				*iter = tolower(*iter);
		}
		*/
		fileLine.push_back(line);
	}
}

void WORD::initWordMap()
{
	std::string word;
	for(std::vector<std::string>::size_type lineNum = 0;lineNum != fileLine.size();++lineNum)
	{
		std::istringstream istr(fileLine[lineNum]);
		while(istr >> word)
		{
			wordMap[word].insert(lineNum);
		}
	}
}

void WORD::openFile(std::ifstream &ifs)
{
	saveFileLine(ifs);
	initWordMap();
}

WORD::setype WORD::findWord(const std::string &word) const
{
	std::map< std::string, setype>::const_iterator iter = wordMap.find(word);

	if(iter != wordMap.end())
	{
		return iter -> second;
	}
	else
	{
		return setype();
	}
}

std::string WORD::getLineText(setype::size_type line) const
{
	return fileLine[line];
}

void print(const WORD::setype &res, const std::string &inputword, const WORD word)
{
	WORD::setype::size_type size = res.size();
	std::cout << std::endl << inputword << " occurs " << size << " times" << std::endl;
	WORD::setype::const_iterator iter = res.begin();
	
	while(iter != res.end())
	{
		std::cout << "(line " << (*iter) + 1 <<") " << word.getLineText(*iter) << std::endl;
		++iter;
	}

}
