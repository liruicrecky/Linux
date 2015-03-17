/*************************************************************************
	> File Name: ./src/textquery.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Mon 16 Mar 2015 03:36:47 PM CST
 ************************************************************************/

#include"textquery.h"

//class Word

void TextQuery::initFile(std::ifstream &ifs)
{
	initWordMap(ifs);
}

void TextQuery::initWordMap(std::ifstream &ifs)
{
	std::string line;
	std::string word;

	while(getline(ifs, line))
	{
		for(std::string::iterator iter = line.begin();iter != line.end();++iter)
		{
			if(ispunct(*iter))
				*iter = ' ';
			if(isupper(*iter))
				*iter = tolower(*iter);
		}
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

std::string TextQuery::getTextLine(TextQuery::line_no line) const
{
	if(line < fileLine.size()){
		return fileLine[line];
	}
}

std::set<TextQuery::line_no> TextQuery::exQuery(const std::string &word) const
{
	std::map<std::string, std::set<TextQuery::line_no> >::const_iterator res = wordMap.find(word);

	if(res == wordMap.end())
		return std::set<TextQuery::line_no>();
	else
		return res -> second;

}

TextQuery::line_no TextQuery::size() const
{
	return fileLine.size();
}
