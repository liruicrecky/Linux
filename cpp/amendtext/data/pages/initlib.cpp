/*************************************************************************
	> File Name: initlib.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Thu 09 Apr 2015 10:19:33 AM CST
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
#include<stdio.h>

#include<iostream>
#include<vector>
#include<map>
#include<utility>
#include<string>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<locale>

using namespace std;

char line[40480];

friso_t friso = friso_new();
friso_config_t config = friso_new_config();
friso_task_t task = friso_new_task();
static int i = 0;

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



void handleFile(char *path)
{
	int flag;
	wifstream ifs(path);
//	wofstream ofs;

	ios::sync_with_stdio(false);
	std::locale::global(std::locale(""));
	wcout.imbue(std::locale(""));
//	ofs.imbue(locale("zh_CN.utf8"));

//	ofs.open("ripepage.lib", ios::app | ios::out);

	wstring pageline;
	wstring::iterator iter;

//	ofs << "<doc>" << endl
//		<< "<docid>" << ++i << "</docid>" << endl
//		<< "<url>" << path << "</url>" << endl
//		<< "<title>";

	while(getline(ifs, pageline)){

		flag = 0;
		for(iter = pageline.begin();iter != pageline.end();++iter){

			if(*iter == L'】' || *iter == L'【')
				*iter = ' ';	
			wcout << *iter;

		}
	//	wcout << *iter;
	//	ofs << pageline.c_str();
	//	for(iter = pageline.begin();iter != pageline.end();++iter){

		//	if(flag)
//			string chr(iter -> begin());
//				ofs << chr;
	//		if(*iter == L'题')
	//			flag = 1;		
//		}
		
	//	ofs << pageline;

	//	wcout << pageline << endl;
		
	}

//	ofs << "</title>" << endl
//		<< "</doc>" << endl;

//	ofs.close();
	ifs.close();

}

void getDir(char *path)
{
	char fpath[128];
	DIR *pDIR;
	struct dirent *dirInfo;

	if(NULL == (pDIR = opendir(path))){

		perror("open dirent error");
		exit(EXIT_FAILURE);
	}

	chdir(path);

	while(NULL != (dirInfo = readdir(pDIR))){

		if(strcmp(dirInfo -> d_name, ".") == 0 || strcmp(dirInfo -> d_name, "..") == 0)
			continue;

		memset(fpath, 0, sizeof(fpath));
		sprintf(fpath, "%s/%s", getcwd(NULL, 0), dirInfo -> d_name);

		if(DT_DIR & dirInfo -> d_type){

			getDir(fpath);
		}

		cout << fpath << endl;
		handleFile(fpath);
	}

	chdir("..");

	closedir(pDIR);
}

int main(int argc, char **argv)
{

	if(1 != friso_init_from_ifile(friso, config, argv[2])){

		cout << "initialize friso and config fail" << endl;
		exit(EXIT_FAILURE);
	}


	getDir(argv[1]);	

	friso_free_task(task);
	friso_free_config(config);
	friso_free(friso);	
	return 0;
}

