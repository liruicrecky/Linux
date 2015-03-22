/*************************************************************************
  > File Name: ./src/func.c
  > Author: Reacky
  > Mail:3277632240@qq.com 
  > Created Time: Thu 26 Feb 2015 08:06:59 PM CST
 ************************************************************************/

#include"2048.h"

void refreshPad(int *pad)
{
	int *twoPad = pad;
	//	┌ ┼ ┬ ┐ └ ┘ ┴ ├ ┤ ● ○ ─ │

	int i, j;

	for(i = 0;i < 9;i++)
	{
		for(j = 0;j < 9;j++)
		{
			if(i % 2 == 0)
			{
				if(i == 0)
				{
					if(j == 0)
						printf("┌─");
					else if(j == 8)
						printf("┐\n");
					else if(j % 2 == 0)
						printf("┬─");
					else
						printf("───");
				}
				else if(i == 8)
				{
					if(j == 0)
						printf("└─");
					else if(j == 8)
						printf("┘\n");
					else if(j % 2 == 0)
						printf("┴─");
					else
						printf("───");
				}
				else
				{
					if(j == 0)
						printf("├─");
					else if(j == 8)
						printf("┤\n");
					else if(j % 2 == 0)
						printf("┼─");
					else
						printf("───");
				}
			}
			else
			{
				if(j == 0)
					printf("│");
				else if(j == 8)
					printf("│\n");
				else if(j % 2 == 0)
					printf("│");
				else
				{
					if(twoPad[i * 9 + j] != 0)
						printf("%4d", twoPad[i * 9 + j]);
					else
						printf("    ");
				}
			}
		}
	}
}

void refineArray(int *fourArr, int *nineArr)
{
	int i, j;
	int k = -1;

	for(i = 0;i < 9;i++)
		for(j = 0;j < 9;j++)
			if(i % 2 != 0)
				if(j != 0 && j != 8 && j % 2 != 0)
					nineArr[i * 9 + j] = fourArr[++k];
}

void initPad(int *pad)
{
	int *fourPad = pad;

	//random pos 6 of(0 - 7)

	int cnt, posNum;
	int num, randomNum;
	int tmp = -1;

	srand((unsigned)time(NULL));

	for(cnt = 0;cnt < 6;)
	{
		posNum = rand() % 7 + 1;

		if(tmp == posNum)
			continue;

		tmp = posNum;

		//random num

		randomNum = rand() % 3 + 1;

		switch(randomNum)
		{
			case 1:
				num = 2;
				break;
			case 2:
				num = 4;
				break;
			case 3 :
				num = 8;
				break;
		}	
		if(fourPad[posNum] == 0)
		{
			fourPad[posNum] = num;
			++cnt;
		}
	}
}

int mergeNum(int *fourArr, int dire)
{
	int *fourPad = fourArr;
	int i, j;
	int tmpi, tmpj;
	int cnt = 0;
	int flag = 0;

	//up
	if(dire == 'i')
	{
		for(i = 1;i < 4;i++)
		{
			flag = 0;
			for(j = 0;j < 4;j++)
			{
				if(fourPad[i * 4 + j] != 0)
				{
					tmpi = i;
					if(fourPad[(i - 1) * 4 + j] == 0)
					{
						while(fourPad[(tmpi - 1) * 4 + j] == 0)
						{
							fourPad[(tmpi - 1) * 4 + j] = fourPad[tmpi * 4 + j];
							fourPad[tmpi * 4 + j] = 0;
							--tmpi;
							if(tmpi == 0)
								break;
						}
						flag = 0;
						if(tmpi == 0)
							continue;
					}
					if(fourPad[(tmpi - 1) * 4 + j] == fourPad[tmpi * 4 + j] && flag == 0)
					{
						fourPad[(tmpi - 1) * 4 + j] *= 2;
						fourPad[tmpi * 4 + j] = 0;
						cnt += fourPad[(tmpi - 1) * 4 + j];
						flag = 1;
					}
					if(fourPad[(tmpi - 1) * 4 + j] != fourPad[tmpi * 4 + j])
					{
						continue;
					}	
				}
			}
		}
	}
	//down
	else if(dire == 'k')
	{
		for(i = 2;i >= 0;i--)
		{
			flag = 0;
			for(j = 0;j < 4;j++)
			{
				if(fourPad[i * 4 + j] != 0)
				{
					tmpi = i;
					if(fourPad[(i + 1) * 4 + j] == 0)
					{
						while(fourPad[(tmpi + 1) * 4 + j] == 0)
						{
							fourPad[(tmpi + 1) * 4 + j] = fourPad[tmpi * 4 + j];
							fourPad[tmpi * 4 + j] = 0;
							++tmpi;
							if(tmpi == 3)
								break;
						}
						flag = 0;
						if(tmpi == 3)
							continue;
					}	
					if(fourPad[(tmpi + 1) * 4 + j] == fourPad[tmpi * 4 + j] && flag == 0)
					{
						fourPad[(tmpi + 1) * 4 + j] *= 2;
						fourPad[tmpi * 4 + j] = 0;
						cnt += fourPad[(tmpi + 1) * 4 + j];
						flag = 1;
					}
					if(fourPad[(tmpi + 1) * 4 + j] != fourPad[tmpi * 4 + j])
					{
						continue;
					}	
				}
			}
		}
	}
	//left
	else if(dire == 'j')
	{
		for(j = 1;j < 4;j++)
		{
			flag = 0;
			for(i = 0;i < 4;i++)
			{
				if(fourPad[i * 4 + j] != 0)
				{
					tmpj = j;
					if(fourPad[i * 4 + j - 1] == 0)
					{
						while(fourPad[i * 4 + tmpj - 1] == 0)
						{
							fourPad[i * 4 + tmpj - 1] = fourPad[i * 4 + tmpj];
							fourPad[i * 4 + tmpj] = 0;
							--tmpj;
							if(tmpj == 0)
								break;
						}
						flag = 0;
						if(tmpj == 0)
							continue;
					}
					if(fourPad[i * 4 + tmpj - 1] == fourPad[i * 4 + tmpj] && flag == 0)
					{
						fourPad[i * 4 + tmpj - 1] *= 2;
						fourPad[i * 4 + tmpj] = 0;
						cnt += fourPad[i * 4 + tmpj - 1];
						flag = 1;
					}
					if(fourPad[i * 4 + tmpj - 1] != fourPad[i * 4 + tmpj])
					{
						continue;
					}	
				}
			}
		}
	}
	//right
	else if(dire == 'l')
	{
		for(j = 2;j >= 0;j--)
		{
			flag = 0;
			for(i = 0;i < 4;i++)
			{
				if(fourPad[i * 4 + j] != 0)
				{
					tmpj = j;
					if(fourPad[i * 4 + j + 1] == 0)
					{
						while(fourPad[i * 4 + tmpj + 1] == 0)
						{
							fourPad[i * 4 + tmpj + 1] = fourPad[i * 4 + tmpj];
							fourPad[i * 4 + tmpj] = 0;
							++tmpj;
							flag = 0;
							if(tmpj == 3)
								break;
						}
						if(tmpj == 3)
							continue;
					}
					if(fourPad[i * 4 + tmpj + 1] == fourPad[i * 4 + tmpj] && flag == 0)
					{
						fourPad[i * 4 + tmpj + 1] *= 2;
						fourPad[i * 4 + tmpj] = 0;
						cnt += fourPad[i * 4 + tmpj + 1];
						flag = 1;
					}
					if(fourPad[i * 4 + tmpj + 1] != fourPad[i * 4 + tmpj])
					{
						continue;
					}
				}
			}
		}
	}

	return cnt;
}

void randomNum(int *fourArr)
{
	int *fourPad = fourArr;
	int i, j, k, index;
	int cnt = 0;

	for(i = 0;i < 4;i++)
	{
		for(j = 0;j < 4;j++)
		{
			if(fourPad[i * 4 + j] == 0)
				++cnt;
		}
	}

	srand(time(NULL));

	int numPos, randNum;

	for(k = 0;k < 1;k++)
	{
		index = 0;
		numPos = rand() % cnt + 1;

		//find pos
		for(i = 0;i < 4;i++)
		{
			for(j = 0;j < 4;j++)
			{
				if(fourPad[i * 4 + j] == 0)
				{
					++index;
					if(index == numPos)
					{
						//put num
						randNum = rand() % 3 + 1;

						switch(randNum)
						{
							case 1:
								fourPad[i * 4 + j] = 2;
								break;
							case 2:
								fourPad[i * 4 + j] = 4;
								break;
							case 3:
								fourPad[i * 4 + j] = 8;
								break;
						}

					}
				}
			}
		}


	}

}

int checkSame(int *fourArr)
{
	int *fourPad = fourArr;
	int i, j;

	for(i = 0;i < 3;++i)
	{
		for(j = 0;j < 3;++j)
		{
			if(fourPad[i * 4 + j] == fourPad[i * 4 + j + 1] || fourPad[i * 4 + j] == fourPad[(i + 1) * 4 + j])
			{
				return 0;
			}
		}
	}

	return 1;
}

int checkWin(int *fourArr)
{
	int *fourPad = fourArr;
	int i, j;
	int cnt = 0;
	for(i = 0;i < 4;i++)
	{
		for(j = 0;j < 4;j++)
		{
			if(fourPad[i * 4 + j] == 2048)
				return 1;
			else if(fourPad[i * 4 + j] == 0)
				++cnt;
		}
	}

	if(cnt == 0 && checkSame(fourArr))
		return -1;
	else
		return 0;
}

