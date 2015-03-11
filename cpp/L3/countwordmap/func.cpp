/*************************************************************************
	> File Name: ./func.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Wed 11 Mar 2015 07:41:18 PM CST
 ************************************************************************/

#include"word.h"

void initFile(std::ifstream &ifs, std::string &path)
{
	std::string line;
	std::string::iterator iter;
	
	std::ofstream ofs(path.c_str());
	
	while(getline(ifs, line))
	{
		iter = line.begin();
		while(iter != line.end())
		{
			if(ispunct(*iter))
				*iter = ' ';
			if(isupper(*iter))
				*iter = tolower(*iter);

			++iter;
		}

		ofs << line << std::endl;
	}

	ofs.close();
}

bool cmp(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
{
	return a.second > b.second;
}


