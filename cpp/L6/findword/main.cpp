/*************************************************************************
	> File Name: main.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Fri 13 Mar 2015 08:27:59 PM CST
 ************************************************************************/

#include"word.h"

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		std::cout << "input path first!" << std::endl;
		return 1;
	}
	std::ifstream ifs(argv[1]);
	if(!ifs)
	{
		std::cout << "open file failed!" << std::endl;
		return 1;
	}


	WORD word;

	word.openFile(ifs);
	std::string inputword;

	while(std::cout << "Input a word you want to search: ", std::cin >> inputword, !std::cin.eof())
	{
		WORD::setype res = word.findWord(inputword);
		print(res, inputword, word);
	}

	return 0;
}

