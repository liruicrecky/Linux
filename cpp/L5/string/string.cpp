/*************************************************************************
	> File Name: string.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Wed 11 Mar 2015 03:40:15 PM CST
 ************************************************************************/

#include"string.h"
#include<string.h>

//create
String::String()
{
	_str = NULL;
}

String::String(const char * c)
{
	_str = new char[strlen(c) + 1];
	strcpy(_str, c);
}

String::String(const String &s)
{
	_str = new char[strlen(s._str) + 1];
	strcpy(_str, s._str);
}

String::~String()
{
	delete _str;
	_str = NULL;
}

//operator

String &String::operator=(const String &s)
{
	if(_str)
	{
		delete _str;
		_str = NULL;
	}

	_str = new char[strlen(s._str) + 1];
	strcpy(_str, s._str);
}

String &String::operator=(const char *c)
{
	if(_str)
	{
		delete _str;
		_str = NULL;
	}

	_str = new char[strlen(c) + 1];
	strcpy(_str, c);
}

char &String::operator[](std::size_t index)
{
	return _str[index];
}

const char &String::operator[](std::size_t index) const
{
	return _str[index];
}

std::size_t String::size() const
{
	if(!_str)
		return 0;
	return strlen(_str);
}

const char *String::c_str() const
{
	return _str;
}

String operator+(const String &a, const String &b)
{
	String res;

	res._str = new char[strlen(a._str) + strlen(b._str) + 1];
	strcpy(res._str, a._str);
	strcat(res._str, b._str);

	return res;
}

String operator+(const String &a, const char *b)
{
	String res;

	res._str = new char[strlen(a._str) + strlen(b) + 1];
	strcpy(res._str, a._str);
	strcat(res._str, b);

	return res;
}

String operator+(const char *a, const String &b)
{
	String res;

	res._str = new char[strlen(a) + strlen(b._str) + 1];
	strcpy(res._str, a);
	strcat(res._str, b._str);

	return res;
}

//compare

bool operator==(const String &a, const String &b)
{
	if(strcmp(a._str, b._str) == 0)
		return 1;
	return 0;
}

bool operator!=(const String &a, const String &b)
{
	if(strcmp(a._str, b._str) != 0)
		return 1;
	return 0;
}

bool operator<(const String &a, const String &b)
{
	if(strcmp(a._str, b._str) < 0)
		return 1;
	return 0;
}

bool operator>(const String &a, const String &b)
{
	if(strcmp(a._str, b._str) > 0)
		return 1;
	return 0;
}

bool operator<=(const String &a, const String &b)
{
	if(strcmp(a._str, b._str) <= 0)
		return 1;
	return 0;
}

bool operator>=(const String &a, const String &b)
{
	if(strcmp(a._str, b._str) >= 0)
		return 1;
	return 0;
}

//iostream

std::ostream &operator<<(std::ostream &os, const String &s)
{
	os << s._str;

	return os;
}

std::istream &operator>>(std::istream &is, String &s)
{
	is >> s._str;

	return is;
}


