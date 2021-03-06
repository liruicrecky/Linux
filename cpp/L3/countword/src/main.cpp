/*************************************************************************
	> File Name: ./src/main.cpp
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Fri 06 Mar 2015 07:43:30 PM CST
 ************************************************************************/

#include"wor.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;


int main(void)
{
	//time cal
	
	time_t handFileBeg, handFileEnd;
	time_t handWorBeg, handWorEnd;

	//file path
	string oname = "/home/liruicheng/LinuxCode/cpp/L3/countword/data/The_Holy_Bible.txt";

	//if init new file
	int ifnew = 0;
	string name;
	std::ifstream ifs;

	cout << "create a new inited file?(y/n)";
	cin >> name;
	
	if(name[0] == 'y')
	{
		cout << "Input a name for the inited file(*.txt):";
		cin >> name;
	
		ifnew = 1;
		handFileBeg = clock();
		initFile(oname, name);
		handFileEnd = clock();
		ifs.open(name.c_str());
	}
	else
		ifs.open(oname.c_str());

	//open ignore file
	
	handWorBeg = clock();

	std::ifstream iifs("/home/liruicheng/LinuxCode/cpp/L3/countword/data/ignore.txt");

	if(!iifs)
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
	size_t cnt;

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
		//not creatr inited file deal the data form old file
		if(!ifnew)
		{
			for(cnt = 0;cnt != line.size();++cnt)
			{
				if(ispunct(line[cnt]))
					line[cnt] = ' ';
				if(isupper(line[cnt]))
					line[cnt] = tolower(line[cnt]);
			}
		}

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
				wor.setWord(str);
				wor.setCnt(1);
				word.push_back(wor);
				continue;
			}

			size = 0;

			for(vector<WOR>::iterator iter = word.begin();iter != word.end();++iter)
			{
				if(iter -> cmpWord(str))
				{
					iter -> addCnt();
					break;
				}

				++size;
			}

			if(size == word.size())
			{
				wor.setWord(str);
				wor.setCnt(1);
				word.push_back(wor);
			}

		}
	}

	handWorEnd = clock();


	cout << endl << "-----WORDS AND LINES-----" << endl
	     << "The words of the txt is: " << cntWord << endl
		 << "The lines of the txt is: " << cntLine << endl;

	//sort
	
	time_t sortBeg, sortEnd;
	
	sortBeg = clock();
	sort(word.begin(), word.end(), cmp);
	sortEnd = clock();

	//print res>

	int i = 1;
	
	cout << endl << "-----TOP TEN-----" << endl;

	for(vector<WOR>::iterator iter = word.begin();iter != word.begin() + 10;++iter)
		cout << i++ << "st word is " << "'" << iter -> getWord() << "'" << " :" << iter -> getCnt() << endl; 

	cout << "-----Time-----" << endl
		 << "handle file time: " << (static_cast<double>(handFileEnd - handFileBeg) / CLOCKS_PER_SEC) << "s" << endl
		 << "handle word time: " << (static_cast<double>(handWorEnd - handWorBeg) / CLOCKS_PER_SEC) << "s" << endl
		 << "       sort time: " << (static_cast<double>(sortEnd - sortBeg) / CLOCKS_PER_SEC) << "s" << endl;
		

	ifs.close();

	return 0;
}

