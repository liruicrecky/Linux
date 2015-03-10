/*************************************************************************
	> File Name: no4.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Tue 10 Mar 2015 10:44:58 AM CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<string.h>
#include<cstdlib>

using std::cout;
using std::endl;
using std::string;

class String
{
public:
	String(const char *str = NULL);
	String(const String &another);
	~String();
	String &operator=(const String &rhs);
	void print()
	{
		cout << m_data << endl;
	}
private:
	char *m_data;
};

String::String(const char *str)
{
	m_data = new char[strlen(str) + 1];
	strcpy(m_data, str);
	cout << "default" << endl;
}
String &String::operator=(const String &rhs)
{
	if(&rhs != this)
	{
		if(m_data)
		{
			delete [] m_data;
			m_data = NULL;
		}
	
		m_data = new char[strlen(rhs.m_data) + 1];
		if(NULL == m_data)
		{
			cout << "memory failed" << endl;
			return *this;
		}
		strcpy(m_data, rhs.m_data);
	}

	cout << "operator" << endl;
	return *this;
}

String::String(const String &another)
{
	m_data = new char[strlen(another.m_data) + 1];
	if(NULL == m_data)
	{
		cout << "memory failed" << endl;
		return;
	}

	strcpy(m_data, another.m_data);

	cout << "copy" << endl;
}


String::~String()
{
	delete [] m_data;
	m_data = NULL;
}

int main(void)
{
	char name[] = "li";
	char name1[] = "wang";
	char name2[] = "ddd";
	String str(name);
	String str1 = str;
	str1 = name2;
	str.print();
	str1.print();

	return 0;
}
