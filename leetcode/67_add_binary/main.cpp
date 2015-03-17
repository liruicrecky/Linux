/*************************************************************************
  > File Name: main.cpp
  > Author: Reacky
  > Mail:327763224@qq.com 
  > Created Time: Tue 17 Mar 2015 09:54:56 AM CST
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;

string addBinary2(string a, string b)
{
	string s = "";

	int c = 0, i = a.size() - 1, j = b.size() - 1;
	while(i >= 0 || j >= 0 || c == 1)
	{
		c += i >= 0 ? a[i --] - '0' : 0;
		c += j >= 0 ? b[j --] - '0' : 0;
		s = char(c % 2 + '0') + s;
		c /= 2;
	}

	return s;


}

string addBinary1(string a, string b) {
	if(a.empty()){
		return b;
	}

	if(b.empty()){
		return a;
	}

	string res;
	string tmp;
	string::reverse_iterator itera, iterb;
	int up = 0;

	for(itera = a.rbegin(), iterb = b.rbegin();itera != a.rend() && iterb != b.rend();++itera, ++iterb){
		tmp = ((*itera + *iterb + up - 2 * '0') % 2) + '0';
		res.insert(0, tmp);
		up = ((*itera + *iterb + up - 2 * '0') / 2) ;
	}

	while(itera != a.rend()){
		tmp = ((*itera + up - '0') % 2) + '0';
		res.insert(0, tmp);
		up = ((*itera + up - '0') / 2) ;
		++itera;
	}
	while(iterb != b.rend()){
		tmp = ((*iterb + up - '0') % 2) + '0';
		res.insert(0, tmp);
		up = ((*iterb + up - '0') / 2) ;
		++iterb;
	}

	if(up == 1){
		res.insert(0, "1");
	}

	return res;
}

string addBinary(string a, string b) {

	if(a.empty()){
		return b;
	}

	if(b.empty()){
		return a;
	}

	string res;
	string tmp;
	string::reverse_iterator itera, iterb;
	int up = 0;

	for(itera = a.rbegin(), iterb = b.rbegin();itera != a.rend() && iterb != b.rend();++itera, ++iterb){
		tmp = ((*itera + *iterb + up - 2 * '0') % 2) + '0';
		res.append(tmp);
		up = ((*itera + *iterb + up - 2 * '0') / 2) ;
	}

	while(itera != a.rend()){
		tmp = ((*itera + up - '0') % 2) + '0';
		res.append(tmp);
		up = ((*itera + up - '0') / 2) ;
		++itera;
	}
	while(iterb != b.rend()){
		tmp = ((*iterb + up - '0') % 2) + '0';
		res.append(tmp);
		up = ((*iterb + up - '0') / 2) ;
		++iterb;
	}

	if(up == 1){
		res.append("1");
	}

	string::iterator riterb = res.begin();
	string::iterator ritere = res.end() - 1;

	char ctmp;

	while(riterb < ritere){
		ctmp = *riterb;
		*riterb = *ritere;
		*ritere = ctmp;
		++riterb;
		--ritere;
	}

	return res;
}

int main(void)
{
	string a("11"), b("1");

	cout << addBinary2(a, b) << endl;

	return 0;
}

