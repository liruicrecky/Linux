/*************************************************************************
	> File Name: ./src/mian.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Thu 26 Feb 2015 08:06:50 PM CST
 ************************************************************************/

#include"2048.h"

int main(int argc, char *argv[])
{
	int pad[9][9];
	int savePad[4][4];
	memset(&savePad[0][0], 0, sizeof(savePad));
	memset(&pad[0][0], 0, sizeof(pad));
	int *ninePad = (int *)pad;
	int *fourPad = (int *)savePad;

	//first init pad(random num)

	initPad(fourPad);
	refineArray(fourPad, ninePad);
	refreshPad(ninePad);

	char buf[10];
	char tmp;
	int dire;
	int cnt;

	while(memset(buf, 0, 10), fgets(buf, 10, stdin) != NULL)
	{
		cnt = -1;
		sscanf(buf, "%c", &tmp);
		dire = tmp;
		while(cnt != 0)
		{
			cnt = mergeNum(fourPad, dire);
			if(cnt == 0)
				continue;
		}
		randomNum(fourPad);
		refineArray(fourPad, ninePad);
		refreshPad(ninePad);
		if(checkWin(fourPad) == 1)
		{
			printf("you win the game\n");
			break;
		}
		else if(checkWin(fourPad) == -1)
		{
			printf("you lose the game!\n");
			break;
		}
		else if(checkWin(fourPad) == 0)
		{
			continue;
		}
	}


	return 0;
}

