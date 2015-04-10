/*************************************************************************
  > File Name: handletf8.cpp
  > Author: Reacky
  > Mail:327763224@qq.com 
  > Created Time: Thu 02 Apr 2015 07:48:02 PM CST
 ************************************************************************/

extern "C" 
{

#include"friso_API.h"
#include"friso.h"

}

#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

#include<iostream>
#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<cmath>

#define PAGENUM 8272

using namespace std;

map<string, int> wcMap;
map<string, int> wordDF;
map<string, map<string, int> > wordTF;
map<string, int> wordTFinit;
vector<string> vecpath;

static int DFcnt;
static string tmpword;

char line[60480];

friso_t friso = friso_new();
friso_config_t config = friso_new_config();
friso_task_t task = friso_new_task();


void getDir(char *path, int mode);
void handleFile(int mode);

void initWordDF()
{
	map<string, int>::const_iterator iter = wcMap.begin();
	for(;iter != wcMap.end();++iter){

		DFcnt = 0;
		tmpword = iter -> first;
		handleFile(1);
		wordDF.insert(make_pair(tmpword, DFcnt));
	}	
}

static fstring getLine(const char *str, fstring __dst ) 
{
	int i = 0;
	register int c;
	register fstring cs;

	cs = __dst;
	while ( ( c = str[i++]) != '\r' ){
		*cs++ = c; 
	}
	*cs = '\0';

	return ( c == EOF && cs == __dst ) ? NULL : __dst;
}

int frisoFile(string &text, int mode, const char *path)
{
	memset(line, 0, sizeof(line));
	getLine(text.c_str(), line);
	friso_set_text(task, line);

	while(NULL != (config -> next_token(friso, config, task))){

		if(mode == 0){

			++wcMap[task -> token -> word];
			++wordTFinit[task -> token -> word];

		}else if(mode == 1){

			if(task -> token -> word == tmpword){

				++DFcnt;
				return 1;
			}
		}
	}

	return 0;
}



void handleFile(int mode)
{
	vector<string>::const_iterator iter;
	for(iter = vecpath.begin();iter != vecpath.end();++iter){

		ifstream ifs((*iter).c_str());
		string line;

		while(getline(ifs, line)){

			if(frisoFile(line, mode, (*iter).c_str()) == 1 && mode == 1)
				break;
		}

		wordTF.insert(make_pair(*iter, wordTFinit));
		wordTFinit.clear();

		ifs.close();
	}
}

void getDir(char *path, int mode)
{
	char fpath[128];
	DIR *pDIR;
	struct dirent *dirInfo;

	if(NULL == (pDIR = opendir(path))){

		perror("open dirent error");
		exit(EXIT_FAILURE);
	}

	cout << path << endl;
	chdir(path);

	while(NULL != (dirInfo = readdir(pDIR))){

		if(strcmp(dirInfo -> d_name, ".") == 0 || strcmp(dirInfo -> d_name, "..") == 0)
			continue;

		memset(fpath, 0, sizeof(fpath));
		sprintf(fpath, "%s/%s", getcwd(NULL, 0), dirInfo -> d_name);

		if(DT_DIR & dirInfo -> d_type){

			getDir(fpath, mode);
		}
		//	cout << fpath << endl;
		//	handleFile(fpath, mode);
	}

	chdir("..");

	closedir(pDIR);
}

void initpath(char *path)
{
	ifstream ifs(path);
	string line;
	while(getline(ifs, line)){

		vecpath.push_back(line);
	}
	ifs.close();
}

void initinvert()
{
	map<int, double> wordQZ;
	vector<int> numDoc;
	double qz, sumqz;
	int cnt;
	map<string, int>::const_iterator iter = wcMap.begin();
	vector<string>::const_iterator veciter;

	map<string, map<string, int> >::const_iterator TFiter;
	map<string, int>::const_iterator TFintiter;
	map<string, int>::const_iterator DFiter;

	ofstream ofs("invert.lib");

	for(;iter != wcMap.end();++iter){
	
		cnt = 0;
		wordQZ.clear();
		numDoc.clear();
		sumqz = 0;
		ofs << iter -> first << " ";
		for(veciter = vecpath.begin();veciter != vecpath.end();++veciter){
			
			++cnt;
			TFiter = wordTF.find(*veciter);
			TFintiter = (TFiter -> second).find(iter -> first);
			DFiter = wordDF.find(iter -> first);
			if(TFintiter == (TFiter -> second).end())
				continue;
			
			qz = (TFintiter -> second) * log(PAGENUM / (DFiter -> second));
			sumqz += qz * qz;
			wordQZ.insert(make_pair(cnt, qz));
			numDoc.push_back(TFintiter -> second);
		}

		vector<int>::const_iterator viter = numDoc.begin();

		for(map<int, double>::const_iterator miter = wordQZ.begin();
			miter != wordQZ.end();
			++miter, ++viter){

			ofs << miter -> first << " " << *viter << " " << (miter -> second) / sqrt(sumqz) << " ";
		}

		ofs << endl;
	}

	ofs.close();
}

int main(int argc, char **argv)
{

	if(1 != friso_init_from_ifile(friso, config, argv[2])){

		cout << "initialize friso and config fail" << endl;
		exit(EXIT_FAILURE);
	}


	//	getDir(argv[1], 0);
	initpath(argv[1]);
	handleFile(0);
	initWordDF();
	initinvert();


	map<string, int>::const_iterator iter = wcMap.begin();
	iter = wordDF.begin();
	for(;iter != wordDF.end();++iter){

		cout << iter -> first << " " << iter -> second << endl;
	}


	friso_free_task(task);
	friso_free_config(config);
	friso_free(friso);	
	return 0;
}

