/*************************************************************************
	> File Name: handlefile.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Sat 28 Mar 2015 10:29:13 AM CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include<sstream>

#include<stdlib.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>
#include<tr1/unordered_map>
using namespace std;
using namespace std::tr1;

map<string, int> wordcnt;

void handlefile(char *path)
{
	bool flag;
	ifstream ifs(path);
	string line, word;
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
			flag = true;
			for(string::iterator witer = word.begin();witer != word.end();++witer)
			{
				if(!isalpha(*witer))
				{
					flag = false;
					break;
				}
			}
			if(flag)
				++wordcnt[word];
		}
	}

	ifs.close();
}

void getDir(char *path)
{
	char fpath[128];
	DIR *pDIR;
	struct dirent *dirInfo;

	if(NULL == (pDIR = opendir(path)))
	{
		perror("opendir error");
		exit(EXIT_FAILURE);
	}

	chdir(path);

	while(NULL != (dirInfo = readdir(pDIR)))
	{
		if(strcmp(dirInfo -> d_name, ".") == 0 || strcmp(dirInfo -> d_name, "..") == 0)
			continue;
		sprintf(fpath, "%s/%s", getcwd(NULL, 0), dirInfo -> d_name);
		if(DT_DIR & dirInfo -> d_type)
		{
			getDir(fpath);
		}
		cout << fpath << endl;
		handlefile(fpath);
	}

	chdir("..");

	closedir(pDIR);
}

int main(int argc, char **argv)
{
	char path[128];
	strcpy(path, argv[1]);
	cout << "processing..." << endl;
	getDir(path);
	ofstream ofs("dictmap.txt");

	for(map<string, int>::iterator miter = wordcnt.begin();miter != wordcnt.end();++miter)
	{
		ofs << miter -> first << " " << miter -> second << endl;
	}

	cout << "file init successfully!" << endl;

	ofs.close();
	return 0;
}
