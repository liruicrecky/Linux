/*************************************************************************
  > File Name: ./smart.h
  > Author: Reacky
  > Mail:327763224@qq.com 
  > Created Time: Tue 17 Mar 2015 02:18:49 PM CST
 ************************************************************************/

#ifndef __SMART_H__
#define __SMART_H__

#include<iostream>

class Ptr
{
	friend class SmartPtr;

	int *pt;
	size_t use;

	Ptr(int *p) : pt(p), use(1) 
	{ 
		std::cout << "Ptr constuctor" << std::endl;
	}
	~Ptr()
	{
		delete pt;
		std::cout << "Ptr distructor" << std::endl;
	}
};

class SmartPtr
{
	public:
		SmartPtr(int *p, int i) : ptr(new Ptr(p)), val(i)
		{
			std::cout << "SmartPtr constructor" << std::endl;
		}

		SmartPtr(const SmartPtr &ori) : ptr(ori.ptr), val(ori.val)
		{
			++ptr -> use;
			std::cout<< "Copy SmaetPtr use: " << ptr -> use  << std::endl;
		}

		SmartPtr &operator=(const SmartPtr &ori)
		{
			++ori.ptr -> use;

			if(--ptr == 0)
			{
				delete ptr;
			}
			val = ori.val;
			ptr = ori.ptr;

			return *this;
		}

		~SmartPtr()
		{
			std::cout << "SmartPtr disconstor called, use = " << ptr -> use << std::endl;
			if(--ptr -> use == 0)
			{
				delete ptr;
			}

		}

		int getVal() const
		{
			return val;
		}

		int *getPtr() const
		{
			return ptr -> pt;
		}

	private:
		Ptr *ptr;
		int val;
};

#endif

