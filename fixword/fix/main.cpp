/*************************************************************************
  > File Name: main.cpp
  > Author: Reacky
  > Mail:327763224@qq.com 
  > Created Time: Tue 17 Mar 2015 11:00:35 PM CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<string.h>
#include<map>
#include<fstream>
#include<sstream>

using namespace std;

int fixnum(const string &a, const string &b)
{

	int m = a.size() + 1;
	int n = b.size() + 1;

	int arry[n][m];

	memset(arry, 0, sizeof(int) * m * n);

	int i, j;

	for(i = 1;i != n;++i)
	{
		for(j = 1;j != m;++j)
		{
			if(a[j - 1] == b[i - 1])
			arry[i][j] = arry[i - 1][j - 1] + 1;
			else
			{
				if(arry[i - 1][j - 1] >= arry[i - 1][j] && arry[i - 1][j - 1] >= arry[i][j - 1])
				{
					arry[i][j] = arry[i - 1][j - 1];
				}
				else if(arry[i - 1][j] >= arry[i - 1][j - 1] && arry[i - 1][j] >= arry[i][j - 1])
				{
					arry[i][j] = arry[i - 1][j];
				}
				else if(arry[i][j - 1] >= arry[i - 1][j - 1] && arry[i][j - 1] >= arry[i - 1][j])
				{
					arry[i][j] = arry[i][j - 1];	
				}
			}
		}

	}

	return arry[b.size()][a.size() - 1];
}

int main(void)
{
	ifstream wordmapifs("init_file.txt");
	ifstream checkfile("text.txt");
	ofstream fix("fix.txt");

	string word;
	string line;
	map<string, int> checkset;

	while(getline(wordmapifs, word))
	{
		++checkset[word];
	}

	wordmapifs.close();

	while(getline(checkfile, line))
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
			if(!checkset.count(word))
			{
				int tmp = -100;
				for(map<string, int>::iterator siter = checkset.begin();siter != checkset.end();++siter)
				{
					if(tmp < fixnum(word, siter -> first))
						tmp = fixnum(word, siter -> first);
				}

				for(map<string, int>::iterator siter = checkset.begin();siter != checkset.end();++siter)
				{
					if(tmp == fixnum(word, siter -> first) && (word.size() == siter -> first.size() || word.size() == siter -> first.size() + 1 || word.size() == siter -> first.size() - 1))
					{
						fix << siter -> first << " ";
						break;
					}
				}

			}
			else
			{
				fix << word << " ";
			}
		}

	}

	checkfile.close();
	fix.close();


	return 0;
}

