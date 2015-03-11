/*************************************************************************
	> File Name: ./word.h
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Wed 11 Mar 2015 07:41:31 PM CST
 ************************************************************************/

#ifndef __WORD_H__
#define __WORD_H__

#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<map>
#include<set>
#include<time.h>


void initFile(std::ifstream &ifs, std::string &path);

bool cmp(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b);


#endif
