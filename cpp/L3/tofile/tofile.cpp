/*************************************************************************
	> File Name: tofile.cpp
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Fri 06 Mar 2015 08:10:19 PM CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<fstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(int argc, char **argv)
{
	std::ofstream ofs("1.txt");

	int k = 1024;
	string str = "LL";

	ofs << "k=   " << k   << endl
		<< "str= " << str << endl;

	ofs.close();

	return 0;
}

