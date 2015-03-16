/*************************************************************************
  > File Name: main.cpp
  > Author: Reacky
  > Mail:327763224@qq.com 
  > Created Time: Mon 16 Mar 2015 05:09:21 PM CST
 ************************************************************************/

#include<iostream>
#include<vector>

using namespace std;

bool searchMatrix(vector<vector<int> > &matrix, int target)
{
	vector<vector<int> >::size_type rowsize, row;
	vector<int>::size_type colsize, col, mid, str, end;

	rowsize = matrix.size();
	colsize = matrix[0].size();
	bool flag = true;

	for(row = 0;row != rowsize;++row){
		if(matrix[row][0] <= target && matrix[row][colsize - 1] >= target){
			flag = false;
			break;
		} 
	}

	if(row == rowsize && flag){
		return false;
	}

	if(target == matrix[row][0]){
		return true;
	}else if(target == matrix[row][colsize - 1]){
		return true;
	}

	str = 0;
	end = colsize - 1;
	while(str <= end){
		mid = (str + end) >> 1;
		if(matrix[row][mid] == target){
			return true;
		}else if(matrix[row][mid] > target){
			end = mid - 1;
		}else if(matrix[row][mid] < target){
			str = mid + 1;
		}
	}

	return false;
}

bool searchMatrix2(vector<vector<int> > &matrix, int target)
{
	int beg, end, mid;

	int m = matrix.size(),
		n = matrix[0].size();

	beg = 0;
	end = m * n - 1;

	while(beg <= end){

		mid = (beg + end) >> 1;
		if(matrix[mid / n][mid % n] == target){
			return true;
		}else if(matrix[mid / n][mid % n] < target){
			beg = mid + 1;
		}else if(matrix[mid / n][mid % n] > target){
			end = mid - 1;
		}
	}

	return false;
}

int main(void)
{
	vector<vector<int> > matrix;
	vector<int> row;

//	row.push_back(1);
	row.push_back(1);
	matrix.push_back(row);

	if(searchMatrix2(matrix, 0))
		cout << "true" << endl;
	else
		cout << "false" << endl;


	return 0;
}
