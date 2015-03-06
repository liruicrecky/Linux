/*************************************************************************
	> File Name: ./src/main.cpp
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Fri 06 Mar 2015 07:43:30 PM CST
 ************************************************************************/

#include"count.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

bool cmp(WOR a, WOR b)
{
	return a.cnt > b.cnt;
}

void initFile(string &oname, string &name)
{
	string line;
	string str;
	int cnt;

	std::ofstream ofs(name.c_str());
	std::ifstream ifs(oname.c_str());

	if(!ifs.good())
	{
		cout << "open file failed" << endl;
		return;
	}
	
	while(getline(ifs, line))
	{
		std::istringstream istr(line);
		
		for(cnt = 0;cnt != line.size();++cnt)
		{
			if(ispunct(line[cnt]))
				line[cnt] = ' ';
			if(isupper(line[cnt]))
				line[cnt] = tolower(line[cnt]);
		}

		ofs << line << std::endl;
	}

	ofs.close();
	ifs.close();
}

int main(void)
{
	//file path
	string oname = "/home/liruicheng/LinuxCode/cpp/L3/countword/data/The_Holy_Bible.txt";

	//init new file
	string name;
	cout << "Input a name for the inited file(*.txt):";
	cin >> name;

	initFile(oname, name);

	//open new file and ignore file
	std::ifstream ifs(name.c_str());
	std::ifstream iifs("/home/liruicheng/LinuxCode/cpp/L3/countword/data/ignore.txt");

	if(!iifs.good())
	{	
		cout << "open ignore file failed" << endl
			 << "read all words of the txt" << endl;
	}

	//init val
	vector<WOR> word;
	vector<WOR>::size_type size;
	vector<string> iword;

	string str;
	string line;

	size_t cntLine = 0;
	size_t cntWord = 0;

	int flag;

	WOR wor;

	//read ignore file
	
	while(getline(iifs, line))
	{
		iword.push_back(line);
	}

	//read file
	
	while(getline(ifs, line))
	{	
		std::istringstream istr(line);

		++cntLine;

		while(istr >> str)
		{
			++cntWord;
			flag = 1;

			for(vector<string>::iterator iter = iword.begin();iter != iword.end();++iter)
			{
				if(*iter == str)
				{
					flag = 0;
					break;
				}
			}

			if(flag == 0)
				continue;

			if(word.size() == 0)
			{
					wor.word = str;
					wor.cnt = 1;
					word.push_back(wor);
					continue;
			}

			size = 0;

			for(vector<WOR>::iterator iter = word.begin();iter != word.end();++iter)
			{
				if((*iter).word == str)
				{
					++(*iter).cnt;
					break;
				}

				++size;

			}

			if(size == word.size())
			{
				wor.word = str;
				wor.cnt = 1;
				word.push_back(wor);
			}

		}
	}


	cout << endl << "-----WORDS AND LINES-----" << endl
	     << "The words of the txt is: " << cntWord << endl
		 << "The lines of the txt is: " << cntLine << endl;

	//sort
	
	sort(word.begin(), word.end(), cmp);

	int i = 1;
	
	cout << endl << "-----TOP TEN-----" << endl;

	for(vector<WOR>::iterator iter = word.begin();iter != word.begin() + 10;++iter)
		cout << i++ << "st word is " << "'" << (*iter).word << "'" << " :" << (*iter).cnt << endl; 

	ifs.close();

	return 0;
}

