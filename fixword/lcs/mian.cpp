/*************************************************************************
  > File Name: mian.cpp
  > Author: Reacky
  > Mail:327763224@qq.com 
  > Created Time: Tue 17 Mar 2015 09:41:52 PM CST
 ************************************************************************/

#include<iostream>
#include<string>
#include<vector>
#include<string.h>
using namespace std;

int main(void)
{
	string a("gccctagcg");
	string b("gcgcaatg");

	int m = a.size() + 1;
	int n = b.size() + 1;

	int arry[n][m];

	memset(arry, 0, sizeof(int) * m * n);

	int i, j;

	for(i = 1;i != n;++i)
	{
		for(j = 1;j != m;++j)
		{
			if(a[j - 1] == b[i - 1])
				arry[i][j] = arry[i - 1][j - 1] + 1;
			else
			{
				if(arry[i - 1][j - 1] >= arry[i - 1][j] && arry[i - 1][j - 1] >= arry[i][j - 1])
				{
					arry[i][j] = arry[i - 1][j - 1];
				}
				else if(arry[i - 1][j] >= arry[i - 1][j - 1] && arry[i - 1][j] >= arry[i][j - 1])
				{
					arry[i][j] = arry[i - 1][j];
				}
				else if(arry[i][j - 1] >= arry[i - 1][j - 1] && arry[i][j - 1] >= arry[i - 1][j])
				{
					arry[i][j] = arry[i][j - 1];	
				}
			}
		}

	}

	cout << "    ";
	for(string::iterator iter = a.begin();iter != a.end();++iter)
		cout << *iter << " ";

	cout << endl;
	int p = -1;
	for(i = 0;i != n;++i)
	{
		if(i != 0)
			cout << b[++p] << " ";
		else
			cout << "  ";
		for(j = 0;j != m;++j)
		{
			cout << arry[i][j] << " ";
		}
		cout << endl;
	}


	cout << endl << arry[b.size()][a.size() - 1] << endl;

	return 0;
}

