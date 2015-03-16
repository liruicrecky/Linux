/*************************************************************************
	> File Name: ./src/mian.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Mon 16 Mar 2015 10:41:13 AM CST
 ************************************************************************/

#include"query.h"
#include"word.h"
#include<stdlib.h>

int main(void)
{
	std::string fileName;
	fileHandel file;

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
			if(cin && c == 'n')
				exit(1);
		}
	}

	//init wordMap
	
	Word word;

	word.initWordMap(file.getIfs());


	return 0;
}


