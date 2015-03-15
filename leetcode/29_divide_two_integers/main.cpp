/*************************************************************************
  > File Name: main.cpp
  > Author: Reacky
  > Mail:327763224@qq.com 
  > Created Time: Sun 15 Mar 2015 06:01:02 PM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;

int main(void)
{
	int max = 2147483647;
	int min = -2147483648;
	bool flag = false;
	long long dividend, divisor;

	cout << "dividend, divisor: ";
	cin >> dividend >> divisor;

	if((dividend > 0 && divisor < 0) || (dividend < 0 && divisor > 0)){
		flag = true;
	}

	if(divisor == 1 || divisor == -1){
		if(dividend == min && divisor == 1){
			cout << "res: " << min << endl;
			return 0;
		}else if(dividend == min && divisor == -1){
			cout << "res: " << max << endl;
			return 0;
		}
		cout << "res: " << (divisor == 1 ? dividend : 0 - dividend) << endl;
		return 0;
	}

	long long a = abs(dividend);
	long long b = abs(divisor);
	long long res = 0;

	while(a >= b){
		long long c = b;
		for(int i = 0;a >= c;++i){
			a -= c;
			c <<= 1;
			res += 1LL << i;
		}
	}

	if(flag){
		res = 0 - res;
	}

	cout << "res: " << res << endl;

	return 0;
}
