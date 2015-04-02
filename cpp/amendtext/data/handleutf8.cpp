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

using namespace std;

map<string, int> wcMap;
char line[20480];



friso_t friso = friso_new();
friso_config_t config = friso_new_config();
friso_task_t task = friso_new_task();



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

void frisoFile(string &text)
{
	memset(line, 0, sizeof(line));
	getLine(text.c_str(), line);
	friso_set_text(task, line);

	while(NULL != (config -> next_token(friso, config, task))){

		++wcMap[task -> token -> word];
	}

}



void handleFile(char *path)
{
	ifstream ifs(path);

	string line;

	while(getline(ifs, line)){

		frisoFile(line);

	}

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

	ofstream ofs("dictmap.txt");

	for(map<string, int>::iterator miter = wcMap.begin();miter != wcMap.end();++miter)
	{
		ofs << miter -> first << " " << miter -> second << endl;
	}


	ofs.close();
	friso_free_task(task);
	friso_free_config(config);
	friso_free(friso);	
	return 0;
}

