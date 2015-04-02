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

extern "C"
{
	 friso_t friso_new(void);
	 friso_config_t friso_new_config(void);
}

void frisoFile(string &str, char *con)
{
	friso_t friso = friso_new();
	friso_config_t config = friso_new_config();

	if(1 != friso_init_from_ifile(friso, config, con)){

		cout << "initialize friso and config fail" << endl;
		exit(EXIT_FAILURE);
	}

	friso_task_t task = friso_new_task();
	fstring text;
	strcpy(text, str.c_str());
	friso_set_text(task, text);

	while(NULL != (config -> next_token(friso, config, task))){

		++wcMap[task -> token -> word];
	}

	friso_free_task(task);
	friso_free_config(config);
	friso_free(friso);	
}



void handleFile(char *path, char *config)
{
	ifstream ifs(path);

	string line;

	ifs >> line;

	frisoFile(line, config);

	ifs.close();

	
}

void getDir(char *path, char *config)
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

		sprintf(fpath, "%s/%s", getcwd(NULL, 0), dirInfo -> d_name);

		if(DT_DIR & dirInfo -> d_type){

			getDir(fpath, config);
		}

		handleFile(fpath, config);

		cout << fpath << endl;
	}

	chdir("..");

	closedir(pDIR);
}

int main(int argc, char **argv)
{
	getDir(argv[1], argv[2]);

	
	ofstream ofs("dictmap.txt");

	for(map<string, int>::iterator miter = wcMap.begin();miter != wcMap.end();++miter)
	{
		ofs << miter -> first << " " << miter -> second << endl;
	}


	ofs.close();
	return 0;
}

