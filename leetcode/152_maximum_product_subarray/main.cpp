/*************************************************************************
	> File Name: main.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Wed 18 Mar 2015 08:31:17 PM CST
 ************************************************************************/

#include<iostream>
#include<stdlib.h>
#include<time.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

using namespace std;

int maxProduct(int A[], int n)
{
	if(n == 0){
		return 0;
	}

	int lmax = A[0];
	int lmin = A[0];
	int glo = A[0];

	for(int i = 1;i != n;++i){
		int copy = lmax;
		lmax = MAX(MAX(A[i], A[i] * lmax), A[i] * lmin);
		lmin = MIN(MIN(A[i], A[i] * copy), A[i] * lmin);
		glo = MAX(glo, lmax);
	}

	return glo;
}

int main(void)
{
	int a[20];

	srand(time(NULL));

	for(int i = 0;i != 20;++i){
		a[i] = rand() % 1000 - 500;
		cout << a[i] << " ";
	}

	cout << endl << maxProduct(a, 20) << endl;

	return 0;
}
