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
#include<vector>
#include<map>
#include<utility>
#include<string>
#include<fstream>
#include<sstream>
#include<algorithm>

using namespace std;
bool cmp(const pair<string, int> &a, const pair<string, int> &b);

map<string, vector<string> > pageMap;
char line[40480];

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

bool cmp(const pair<string, int> &a, const pair<string, int> &b)
{
	return a.second > b.second;
}

void handleFile(char *path)
{
	ifstream ifs(path);

	string pageline;
	vector<string> pagetop;
	map<string, int> wordmap;

	while(getline(ifs, pageline)){

		memset(line, 0, sizeof(line));
		getLine(pageline.c_str(), line);
		friso_set_text(task, line);

		while(NULL != (config -> next_token(friso, config, task))){

			++wordmap[task -> token -> word];
		}
	}

	//sort map
	
	vector<pair<string, int> > pairvec;
	vector<pair<string, int> >::const_iterator pairveciter;

	for(map<string, int>::const_iterator iter = wordmap.begin();iter != wordmap.end();++iter){

		pairvec.push_back(make_pair(iter->first, iter->second));
	}

	sort(pairvec.begin(), pairvec.end(), cmp);

	pairveciter = pairvec.begin();
	int end = pairvec.size();
	if(end > 20){
		end = 20;
	}
	for(int i = 0;i != end;++pairveciter, ++i){

		pagetop.push_back(pairveciter -> first);
	}

	pageMap.insert(make_pair(path, pagetop));
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

void delRepeatPage()
{
	map<string, vector<string> >::iterator map_iter, map_iternext, tmpiter;
	map_iter =  pageMap.begin();
	int cnt;
	int total = 0;

	for(;map_iter != pageMap.end();++map_iter){

		tmpiter = map_iter;
		for(map_iternext = ++tmpiter;map_iternext != pageMap.end();++map_iternext){

			cnt = 0;
			vector<string>::iterator vec_iter, vec_iternext;
			vec_iter = (map_iter -> second).begin();
			vec_iternext = (map_iternext -> second).begin();

			for(;vec_iter != (map_iter -> second).end() && vec_iternext != (map_iternext -> second).end();++vec_iter, ++vec_iternext){

				if(*vec_iter == *vec_iternext)
					++cnt;
			}
			//jude

			if(cnt >= 15 ){

				unlink((map_iternext -> first).c_str());
				cout << "del repeat file: " << map_iternext -> first << " " << "times: " << cnt << endl;
				pageMap.erase(map_iternext);
				++total;
			}
		}	
	}

	cout << "totle del repeat pages: " << total << endl;
	
}

int main(int argc, char **argv)
{

	if(1 != friso_init_from_ifile(friso, config, argv[2])){

		cout << "initialize friso and config fail" << endl;
		exit(EXIT_FAILURE);
	}


	getDir(argv[1]);

	delRepeatPage();	

	friso_free_task(task);
	friso_free_config(config);
	friso_free(friso);	
	return 0;
}

