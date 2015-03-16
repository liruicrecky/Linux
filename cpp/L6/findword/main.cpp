/*************************************************************************
  > File Name: main.cpp
  > Author: Reacky
  > Mail:327763224@qq.com 
  > Created Time: Fri 13 Mar 2015 08:27:59 PM CST
 ************************************************************************/

#include"word.h"
#include<stdlib.h>

int main(void)
{
	std::string path;

	fileHandle file;

	while(std::cout << "Input a path(*.*): ", std::cin >> path)
	{
		try{
			file.openFile(path);
			break;
		}catch(std::runtime_error err){
			std::cout << err.what() << std::endl
				<< "Input again?(y/n)" << std::endl;
			char c;
			std::cin >> c;
			if(std::cin && c == 'n')
				exit(1);
		}
	}

	/*
	   if(!ifs)
	   {
	   std::cout << "open file failed!" << std::endl;
	   return 1;
	   }
	   */


	WORD word;

	word.openFile(file.getIfs());

	std::string inputword;

	while(std::cout << "Input a word you want to search: ", std::cin >> inputword, !std::cin.eof())
	{
		WORD::setype res = word.findWord(inputword);
		print(res, inputword, word);
	}

	std::cout << std::endl;

	return 0;
}

