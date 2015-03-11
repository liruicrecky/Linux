/*************************************************************************
	> File Name: ./string.h
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Wed 11 Mar 2015 03:40:25 PM CST
 ************************************************************************/

#ifndef __STRING_H__
#define __STRING_H__

#include<iostream>
#include<string>

class String
{
	char *_str;
public:
	String();
	String(const char *);
	String(const String&);
	~String();

	String &operator=(const String &);
	String &operator=(const char *);

	char &operator[](std::size_t index);
	const char &operator[](std::size_t index) const;

	std::size_t size() const;
	const char * c_str() const;

	friend String operator+(const String &, const String &);
	friend String operator+(const String &, const char *);
	friend String operator+(const char *, const String &);

	friend bool operator==(const String &, const String &);
	friend bool operator!=(const String &, const String &);

	friend bool operator<(const String &, const String &);
	friend bool operator>(const String &, const String &);
	friend bool operator<=(const String &, const String &);
	friend bool operator>=(const String &, const String &);

	friend std::ostream &operator<<(std::ostream &os, const String &s);
	friend std::istream &operator>>(std::istream &is, String &s);


};


#endif

