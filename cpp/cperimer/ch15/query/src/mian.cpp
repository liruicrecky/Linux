/*************************************************************************
	> File Name: ./src/mian.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Mon 16 Mar 2015 10:41:13 AM CST
 ************************************************************************/

#include"query.h"
#include<stdlib.h>

void print(const std::set<TextQuery::line_no> &res, const TextQuery &file)
{
	typedef std::set<TextQuery::line_no> line_nums;
	
	line_nums::size_type size = res.size();

	std::cout << "match occurs " << size << " times" << std::endl;

	line_nums::const_iterator iter = res.begin();

	for(;iter != res.end();++iter)
		std::cout << "(line " << (*iter) + 1 << file.getTextLine(*iter) << std::endl;

}

int main(void)
{
	std::string fileName;
	fileHandle file;

	//open file
	
	while(std::cout << "Input a file name(*.*): ", std::cin >> fileName)
	{
		try
		{
			file.open(fileName);
			break;
		}catch(std::runtime_error err){
			std::cout << err.what() << std::endl
				      << "Input again(y/n): ";
			char c;
			std::cin >> c;
			if(std::cin && c == 'n')
				exit(1);
		}
	}

	//init wordMap
	
	TextQuery word;

	word.initFile(file.getIfs());


	Query q;

	typedef std::set<TextQuery::line_no> line_numbers;

	while(std::cout << "Executed Query for: ", std::cin >> q, !std::cin.eof())
	{
		const line_numbers &res = q.eval(word);
		print(res, word);

	}

	return 0;
}


