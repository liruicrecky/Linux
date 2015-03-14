/*************************************************************************
	> File Name: main.cpp
	> Author: Reacky
	> Mail:327763224@qq.com 
	> Created Time: Sat 14 Mar 2015 09:21:44 PM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
#include<time.h>
#include<stdlib.h>

void print(int x[], int m)
{
	for(int i = 0;i != m; ++i)
		std::cout << x[i] << " ";
	std::cout << std::endl;
}

void merge(int A[], int m, int B[], int n)
{
	int i = m - 1, j = n - 1;
	
	for(int k = m + n - 1;k >= 0;--k)
	{
		if(j < 0){
			A[k] = A[i--];
		}else if(i < 0){
			A[k] = B[j--];
		}else{
			if(A[i] > B[j]){
				A[k] = A[i--];
			}else{
				A[k] = B[j--];
			}
		}
	}

}

void merge2(int A[], int m, int B[], int n)
{
	int i = m - 1, j = n - 1;

	while(j >= 0){

		while(i >= 0 && A[i] > B[j]){
			A[i + j + 1] = A[i];
			--i;
		}
		while(i >= 0 && A[i] < B[j]){
			A[i + j + 1] = A[j];
			--j;
		}
		while(i == -1 && j >=0){
			A[j] = B[j];
			--j;
		}

	}

}


int main(void)
{
	int i;
	int *a = new int[100];
	int *b = new int[28];

	srand(time(NULL));

	for(i = 0;i != 50;++i)
		a[i] = rand() % 1000 + 1;

	for(i = 0;i != 20;++i)
		b[i] = rand() % 1000 + 1;

	std::sort(a, a + 50);
	std::sort(b, b + 20);

	print(a, 50);
	std::cout << std::endl;
	print(b, 20);
	std::cout << std::endl;

	merge2(a, 50, b, 20);

	print(a, 70);

	delete [] a;
	delete [] b;

	return 0;
}
