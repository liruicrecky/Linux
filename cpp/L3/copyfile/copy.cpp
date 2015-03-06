/*************************************************************************
	> File Name: copy.cpp
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Fri 06 Mar 2015 08:14:45 PM CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<fstream>

using std::cout;
using std::endl;
using std::string;

int main(void)
{
	std::ifstream ifs("bible.txt");

	if(!ifs.good())
	{
		cout << "open file failed" << endl;
		return -1;
	}

	std::ofstream ofs("text.txt");
	string line;

	while(getline(ifs, line))
	{
		ofs << line << endl;
	}

	ifs.close();
	ofs.close();

	return 0;
}
