/*************************************************************************
	> File Name: ./src/vsai.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Thu 26 Feb 2015 10:42:36 AM CST
 ************************************************************************/

#include"gobang.h"

int main(int agrc, char *argv[])
{
	char clientColor, aiColor;
	printf("Please input you color!(1 for white, 2 for black)\n");
	scanf("%c", & clientColor);

	if(clientColor == '1')
		aiColor = '2';
	else
		aiColor = '1';

	char chessesPad[15][15];
	memset(chessesPad, '0', sizeof(char) * 225);
	char * pchPad = (char *)chessesPad;
	refreshChessesPad(pchPad);

	char buf[10];
	int x, y;

	while(memset(buf, 0, 10), fgets(buf, 10, stdin) != NULL)
	{
		sscanf(buf, "%d %d", &x, &y);
		--x;
		--y;
		if(x > 14 || x < 0 || y > 14 || y < 0)
		{
			printf("invalid num!\n");
			continue;
		}
		else if(chessesPad[x][y] != '0')
		{
			printf("aleady exist! find another place!\n");
			continue;
		}
		else
		{
			chessesPad[x][y] = clientColor;
			refreshChessesPad(pchPad);
			if(checkWin(pchPad, clientColor))
			{	
				printf("you win the game!\n");
				break;
			}
			aiChesses(pchPad, aiColor);
			refreshChessesPad(pchPad);
			if(checkWin(pchPad, aiColor))
			{
				printf("you lose the game!\n");
				break;
			}
		}
	}

	return 0;
}
