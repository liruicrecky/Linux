/*************************************************************************
	> File Name: main.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Tue 17 Mar 2015 09:12:02 PM CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<map>

using namespace std;

int main(void)
{
	string line, word;
	ifstream ifs("The_Holy_Bible.txt");
	ofstream ofs("init_file.txt");

	map<string, int> wordmap;

	while(getline(ifs, line))
	{
		for(string::iterator iter = line.begin();iter != line.end();++iter)
		{
			if(ispunct(*iter))
				*iter = ' ';
			if(isupper(*iter))
				*iter = tolower(*iter);
		}

		istringstream istr(line);
		while(istr >> word)
		{
			++wordmap[word];
		}

	}

	int cnt = -1;

	for(map<string, int>::iterator miter = wordmap.begin();miter != wordmap.end();++miter)
	{
		if(!isdigit(miter -> first[0]))
		{
			ofs << miter -> first << endl;
			++cnt;
		}
	}

	cout << cnt << endl;

	ifs.close();
	ofs.close();

	return 0;
}

