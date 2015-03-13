/*************************************************************************
	> File Name: mian.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Wed 11 Mar 2015 07:40:57 PM CST
 ************************************************************************/

#include"word.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;

static const string path("/home/liruicheng/LinuxCode/cpp/L3/countword/data");

int main(void)
{
	string file = path + "/The_Holy_Bible.txt";
	string igfile = path + "/ignore.txt";

	int initfile = 0;
	string word;
	std::ifstream ifs(file.c_str());

	time_t hstart, hend;

	//if init file;
	
	cout << "Init a new file?(y/n): ";
	cin >> word;

	if(word[0] == 'y')
	{
		cout << "Input a file name(*.txt): ";
		cin >> word;

		hstart = clock();
		initFile(ifs, word);
		hend = clock();

		initfile = 1;
		ifs.close();
		ifs.open(word.c_str());
	}

	//init ignore file
	
	std::set<string> exclude;
	string igword;
	std::ifstream iifs(igfile.c_str());

	while(iifs >> igword)
	{
		exclude.insert(igword);
	}

	//handle file
	
	time_t wstart, wend;
	
	int wordCnt = 0;
	int lineCnt = 0;
	
	string line;

	string::iterator iter;

	std::map<string, int> wordCount;

	wstart = clock();
	while(getline(ifs, line))
	{
		++lineCnt;
		if(0 == initfile)
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
		}

		std::istringstream istr(line);

		while(istr >> word)
		{
			++wordCnt;
			if(!exclude.count(word))
				++wordCount[word];
		}
	}
	wend = clock();

	ifs.close();

	//sort map
	
	time_t sstart, send;

	sstart = clock();

	vector< std::pair<string, int> > pairvec;
	for(std::map<string, int>::iterator miter = wordCount.begin();miter != wordCount.end();++miter)
	{
		pairvec.push_back(make_pair(miter -> first, miter -> second));
	}

	sort(pairvec.begin(), pairvec.end(), cmp);

	send = clock();

	//print
	
	cout << endl << "----------Word and Line----------" << endl
	     << "Totle Words: " << wordCnt << endl
	     << "Totle Lines: " << lineCnt << endl;

	cout << endl << "----------Top Ten----------" << endl;

	vector< std::pair<string, int> >::iterator mapiter = pairvec.begin();
	for(int i = 0;i != 10;++mapiter)
		cout << ++i << "st word '" << (mapiter -> first) <<"' : " << (mapiter -> second) << endl;

	cout << endl << "----------Time----------" << endl
		 << "Init file time  : " << (static_cast<double>(hend - hstart) / CLOCKS_PER_SEC) << "s" << endl
		 << "Handle word time: " << (static_cast<double>(wend - wstart) / CLOCKS_PER_SEC) << "s" << endl
		 << "Sort time       : " << (static_cast<double>(send - sstart) / CLOCKS_PER_SEC) << "s" << endl;

	return 0;
}

