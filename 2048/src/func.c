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

void mergeNum(int *fourArr, int dire)
{
	char inputDire = dire
	if(direction == 24)
}

void randomNum(int *fourArr)
{

}

