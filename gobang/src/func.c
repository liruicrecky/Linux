/*************************************************************************
	> File Name: ./src/func.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Mon 23 Feb 2015 02:08:36 PM CST
 ************************************************************************/

#include"gobang.h"

void refreshChessesPad(char *pad)
{
	system("clear");
	int i, j, k = 0;
	char *chPad = pad;
	//	┌ ┼ ┬ ┐ └ ┘ ┴ ├ ┤ ● ○ ─ │

	printf("  ");
	for(i = 1;i <= 15;++i)
	{
		printf("%d ", i % 10);
	}

	printf("\n");

	for(i = 0;i < 15;i++)
	{
		for(j = 0;j < 15;j++)
		{
			if(j == 0)
			{
				printf("%d ", ++k % 10);
			}
			if(i == 0)
			{
				if(chPad[15 * i + j] == '0')
				{
					if(j == 0)
						printf("┌─");
					else if(j == 14)
						printf("┐\n");
					else
						printf("┬─");
				}
				else if(chPad[15 * i + j] == '1')
					printf("●─");
				else
					printf("○─");
			}

 		if(i == 14)
			{
				if(chPad[15 * i + j] == '0')
				{
					if(j == 0)
						printf("└─");
					else if(j == 14)
						printf("┘\n");
					else
						printf("┴─");
				}
				else if(chPad[15 * i + j] == '1')
					printf("●─");
				else
					printf("○─");
			}

			if(i != 0 && i !=14)
			{
				if(chPad[15 * i + j] == '0')
				{
					if(j == 0)
						printf("├─");
					else if(j == 14)
						printf("┤\n");
					else
						printf("┼─");
				}
				else if(chPad[15 * i + j] == '1')
					printf("●─");
				else
					printf("○─");
			}
		}
	}
}

int checkWin(char *pad, char color)
{
	char *chPad = pad;
	int i, j, cent;
	int tmpi, tmpj;
	char tmp;

	for(i = 0;i < 15;i++)
	{
		for(j = 0; j < 15;j++)
		{
			if(chPad[i * 15 + j] == color)
			{
				tmp = chPad[i * 15 + j];
				//row
				cent = 1;
				tmpi = i;
				tmpj = j;
				while(tmp == chPad[tmpi * 15 + ++tmpj])
				{
					++cent;
					if(cent == 5)
						return 1;
					if(tmpj == 15)
						break;
				}
				//col
				cent = 1;
				tmpi = i;
				tmpj = j;
				while(tmp == chPad[++tmpi * 15 + j])
				{
					++cent;
					if(cent == 5)
						return 1;
					if(tmpi == 15)
						break;
				}
				//slant
				cent = 1;
				tmpi = i;
				tmpj = j;
				while(tmp == chPad[++tmpi * 15 + ++tmpj])
				{
					++cent;
					if(cent == 5)
						return 1;
					if(tmpi == 15 || tmpj == 15)
						break;
				}
				cent = 1;
				tmpi = i;
				tmpj = j;
				while(tmp == chPad[++tmpi * 15 + --tmpj])
				{
					++cent;
					if(cent == 5)
						return 1;
					if(tmpi == -1 || tmpj == -1)
						break;
				}
			}
		}
	}

	return 0;
}

int aiJudgePad(char *pad, char color, int x, int y)
{
	char *chPad = pad;
	if(x == 0 || x == 14 || y == 0 || y == 14)
		return 0;
	if(chPad[x * 15 + y] != '0')
		return 0;
	if(chPad[x * 15 + y - 1] == color || chPad[(x + 1) * 15 + y] == color || chPad[(x - 1) * 15 + y] == color)
	{
		return 1;
	}

	return 0;
}


void aiChesses(char *pad, char color)
{
	char *chPad = pad;
	char vsColor;
	char tmp;
	int i, j, pos;
	int tmpi, tmpj, cent;

	if(color == '1')
		vsColor = '2';
	else
		vsColor = '1';

	for(i = 0;i < 15;i++)
	{
		for(j = 0; j < 15;j++)
		{
			if(chPad[i * 15 + j] == vsColor)
			{
				tmp = chPad[i * 15 + j];
				
				//row
				cent = 1;
				tmpi = i;
				tmpj = j;
				while(tmp == chPad[tmpi * 15 + ++tmpj])
				{
					++cent;
					if(cent == 2 && chPad[i * 15 + j - 1] == '0' && chPad[i * 15 + j - 2] == vsColor)
					{
						chPad[i * 15 + j - 1] = color;
						return;
					}
					if(cent == 2 && chPad[i * 15 + j + 1] == '0' && chPad[i * 15 + j + 2] == vsColor)
					{
						chPad[i * 15 + j + 1] = color;
						return;
					}
					if(cent == 3 && chPad[i * 15 + j - 1] == '0' && chPad[tmpi * 15 + tmpj + 1] == '0')
					{
						if(aiJudgePad(chPad, color, i, j - 1))
						{
							chPad[i * 15 + j - 1] = color;
							return;
						}
						else if(aiJudgePad(chPad, color, tmpi, tmpj + 1))
						{
							chPad[tmpi * 15 + tmpj + 1] = color;
							return;
						}
						else
						{
						    pos = random() % 2 + 1;
							if(pos == 1)
							{
								chPad[i * 15 + j - 1] = color;
								return;
							}
							else
							{
								chPad[tmpi * 15 + tmpj + 1] = color;
								return;
							}
						}
					}
					if(cent == 4)
					{
						if(chPad[i * 15 + j - 1] == '0')
						{
							chPad[i * 15 + j - 1] = color;
							return;
						}
						else if(chPad[tmpi * 15 + tmpj + 1] == '0')
						{
							chPad[tmpi * 15 + tmpj + 1] = color;
							return;
						}
						
					}
					if(tmpj == 15)
						break;
				}
				//col
				cent = 1;
				tmpi = i;
				tmpj = j;
				while(tmp == chPad[++tmpi * 15 + tmpj])
				{
					++cent;
					if(cent == 2 && chPad[(i - 1) * 15 + j] == '0' && chPad[(i - 2) * 15 + j] == vsColor)
					{
						chPad[(i - 1) * 15 + j] = color;
						return;
					}
					else if(cent == 2 && chPad[(i + 1) * 15 + j] == '0' && chPad[(i + 2) * 15 + j] == vsColor)
					{
						chPad[(i + 1) * 15 + j] = color;
						return;
					}
					if(cent == 3 && chPad[(i - 1) * 15 + j] == '0' && chPad[(tmpi + 1) * 15 + j] == '0')
					{
						if(aiJudgePad(chPad, color, i - 1, j))
						{
							chPad[(i - 1) * 15 + j] = color;
							return;
						}
						else if(aiJudgePad(chPad, color, tmpi + 1, j))
						{
							chPad[(tmpi + 1) * 15 + j] = color;
							return;
						}
						else
						{
						    pos = random() % 2 + 1;
							if(pos == 1)
							{
								chPad[(i - 1) * 15 + j] = color;
								return;
							}
							else
							{
								chPad[(tmpi + 1) * 15 + tmpj] = color;
								return;
							}	
						}
					}
					if(cent == 4)
					{
						if(chPad[(i - 1) * 15 + j] == '0')
						{
							chPad[(i - 1) * 15 + j] = color;
							return;
						}
						else if(chPad[(tmpi + 1) * 15 + j] == '0')
						{
							chPad[(tmpi + 1) * 15 + j] = color;
							return;
						}
					}
					if(tmpi == 15)
						break;
				}
				//slant
				cent = 1;
				tmpi = i;
				tmpj = j;
				while(tmp == chPad[++tmpi * 15 + ++tmpj])
				{
					++cent;
					if(cent == 2 && chPad[(i - 1) * 15 + j - 1] == '0' && chPad[(i - 2) * 15 + j - 2] == vsColor)
					{
						chPad[(i - 1) * 15 + j - 1] = color;
						return;
					}
					else if(cent == 2 && chPad[(i + 1) * 15 + j + 1] == '0' && chPad[(i + 2) * 15 + j + 2] == vsColor)
					{
						chPad[(i + 1) * 15 + j + 1] = color;
						return;
					}
					if(cent == 3 && chPad[(i - 1) * 15 + j - 1] == '0' && chPad[(tmpi + 1) * 15 + tmpj + 1] == '0')
					{
						if(aiJudgePad(chPad, color, i - 1, j - 1))
						{
							chPad[(i - 1) * 15 + j - 1] = color;
							return;
						}
						else if(aiJudgePad(chPad, color, tmpi + 1, tmpj + 1))
						{
							chPad[(tmpi + 1) * 15 + tmpj + 1] = color;
							return;
						}
						else
						{
						    pos = random() % 2 + 1;
							if(pos == 1)
							{
								chPad[(i - 1) * 15 + j - 1] = color;
								return;
							}
							else
							{
								chPad[(tmpi + 1) * 15 + tmpj + 1] = color;
								return;
							}	
						}
					}
					if(cent == 4)
					{
						if(chPad[(i - 1) * 15 + j - 1] == '0')
						{
							chPad[(i - 1) * 15 + j - 1] = color;
							return;
						}
						else if(chPad[(tmpi + 1) * 15 + tmpj + 1] == '0')
						{
							chPad[(tmpi + 1) * 15 + tmpj + 1] = color;
							return;
					}
					}
					if(tmpi == 15 || tmpj == 15)
						break;
				}

				cent = 1;
				tmpi = i;
				tmpj = j;
				while(tmp == chPad[++tmpi * 15 + --tmpj])
				{
					++cent;
					if(cent == 2 && chPad[(i - 1) * 15 + j + 1] == '0' && chPad[(i - 2) * 15 + j + 2] == vsColor)
					{
						chPad[(i - 1) * 15 + j + 1] = color;
						return;
					}
					else if(cent == 2 && chPad[(i + 1) * 15 + j - 1] == '0' && chPad[(i + 2) * 15 + j - 2] == vsColor)
					{
						chPad[(i + 1) * 15 + j - 1] = color;
						return;
					}
					if(cent == 3 && chPad[(i - 1) * 15 + j + 1] == '0' && chPad[(tmpi + 1) * 15 + tmpj - 1] == '0')
					{
						if(aiJudgePad(chPad, color, i - 1, j + 1))
						{
							chPad[(i - 1) * 15 + j + 1] = color;
							return;
						}
						else if(aiJudgePad(chPad, color, tmpi + 1, tmpj - 1))
						{
							chPad[(tmpi + 1) * 15 + tmpj - 1] = color;
							return;
						}
						else
						{
						    pos = random() % 2 + 1;
							if(pos == 1)
							{
								chPad[(i - 1) * 15 + j + 1] = color;
								return;
							}
							else
							{
								chPad[(tmpi + 1) * 15 + tmpj - 1] = color;
								return;
							}	
						}
					}
					if(cent == 4)
					{
						if(chPad[(i - 1) * 15 + j + 1] == '0')
						{
							chPad[(i - 1) * 15 + j + 1] = color;
							return;
						}
						else if(chPad[(tmpi + 1) * 15 + tmpj - 1] == '0')
						{
							chPad[(tmpi + 1) * 15 + tmpj - 1] = color;
							return;
						}
					}
					if(tmpi == -1 || tmpj == -1)
						break;
				}	

			}
		}
	}

	//self 
	
	AIPOS aiPos;

	aiPos.maxCent = -1;
	aiPos.mode = 0;

	for(i = 0;i < 15;i++)
	{
		for(j = 0;j < 15;j++)
		{	
			if(chPad[i * 15 + j] == color)
			{
				tmp = chPad[i * 15 + j];

				//row
				cent = 1;
				tmpi = i;
				tmpj = j;
				while(tmp == chPad[tmpi * 15 + ++tmpj])
				{
					++cent;
					if(cent > aiPos.maxCent)
					{
						aiPos.maxCent = cent;
						aiPos.sx = i;
						aiPos.sy = j;
						aiPos.ex = tmpi;
						aiPos.ey = tmpj;
						aiPos.mode = 1;
					}
					if(tmpj == 15)
						break;
				}

				//col
				cent = 1;
				tmpi = i;
				tmpj = j;
				while(tmp == chPad[++tmpi * 15 + tmpj])
				{	
					++cent;
					if(cent > aiPos.maxCent)
					{
						aiPos.maxCent = cent;
						aiPos.sx = i;
						aiPos.sy = j;
						aiPos.ex = tmpi;
						aiPos.ey = tmpj;
						aiPos.mode = 2;
					}
					if(tmpi == 15)
						break;
				}

				//slant
				cent = 1;
				tmpi = i;
				tmpj = j;
				while(tmp == chPad[++tmpi * 15 + ++tmpj])
				{
					++cent;
					if(cent > aiPos.maxCent)
					{
						aiPos.maxCent = cent;
						aiPos.sx = i;
						aiPos.sy = j;
						aiPos.ex = tmpi;
						aiPos.ey = tmpj;
						aiPos.mode = 3;
					}
					if(tmpi == 15 || tmpj == 15)
						break;
				}

				cent = 1;
				tmpi = i;
				tmpj = j;
				while(tmp == chPad[++tmpi * 15 + --tmpj])
				{
					++cent;
					if(cent > aiPos.maxCent)
					{
						aiPos.maxCent = cent;
						aiPos.sx = i;
						aiPos.sy = j;
						aiPos.ex = tmpi;
						aiPos.ey = tmpj;
						aiPos.mode = 4;
					}
					if(tmpi == -1 || tmpj == -1)
						break;
				}
			}
		}
	}
	//aipos
	
	if(aiPos.mode == 0)
	{
		for(i = 0;i < 15;i++)
		{
			for(j = 0; j < 15;j++)
			{
				if(chPad[i * 15 + j] == vsColor)
				{
					if(i == 0)
					{
						chPad[(i + 1) * 15 + j] = color;
						return;
					}
					else if(i == 14)
					{
						chPad[(i - 1) * 15 + j] = color;
						return;
					}
					else if(j == 0)
					{
						chPad[i * 15 + j + 1] = color;
						return;
					}
					else if(j == 14)
					{
						chPad[i * 15 + j - 1] = color;
						return;
					}
					else
					{
						if(aiPos.maxCent == -1)
						{
							for(tmpi = 0;tmpi < 15;tmpi++)
							{
								for(tmpj = 0;tmpj < 15;tmpj++)
								{		
									if(chPad[tmpi * 15 + tmpj] == color)
									{
										if(chPad[(tmpi - 1) * 15 + tmpj] == '0')
										{
											chPad[(tmpi - 1) * 15 + tmpj] = color;
											return;
										}
										else if(chPad[(tmpi + 1) * 15 + tmpj] == '0')
										{
											chPad[(tmpi + 1) * 15 + tmpj] = color;
											return;
										}
										else if(chPad[tmpi * 15 + tmpj + 1] == '0')
										{
											chPad[tmpi * 15 + tmpj + 1] = color;
											return;
										}
										else if(chPad[tmpi* 15 + tmpj - 1] == '0')
										{
											chPad[tmpi * 15 + tmpj - 1] = color;
											return;
										}
									}
								}
							}

							chPad[i * 15 + j + 1] = color;
							return;						
						}
					}
				}
			}
		}
	}
	
	//row
	if(aiPos.mode == 1)
	{
		if(aiJudgePad(chPad, color, aiPos.sx, aiPos.sy - 1))
		{
			chPad[aiPos.sx * 15 + aiPos.sy - 1] = color;
			return;
		}
		else if(aiJudgePad(chPad, color, aiPos.ex, aiPos.ey + 1))
		{
			chPad[aiPos.ex * 15 + aiPos.ey + 1] = color;
			return;
		}
		else
		{
			for(tmpi = aiPos.sx - 1, tmpj = aiPos.sy;tmpj < aiPos.ey;tmpj++)
			{
				if(aiJudgePad(chPad, color, tmpi, tmpj))
				{
					chPad[tmpi * 15 + tmpj] = color;
					return;
				}
			}

			for(tmpi = aiPos.sx + 1, tmpj = aiPos.sy;tmpj < aiPos.ey;tmpj++)
			{
				if(aiJudgePad(chPad, color, tmpi, tmpj))
				{
					chPad[tmpi * 15 + tmpj] = color;
					return;
				}
			}	
		}
		
	}
	//col
	if(aiPos.mode == 2)
	{
		if(aiJudgePad(chPad, color, aiPos.sx - 1, aiPos.sy))
		{
			chPad[(aiPos.sx - 1) * 15 + aiPos.sy] = color;
			return;
		}
		else if(aiJudgePad(chPad, color, aiPos.ex + 1, aiPos.ey))
		{
			chPad[(aiPos.ex + 1) * 15 + aiPos.ey] = color;
			return;
		}
		else
		{
			for(tmpi = aiPos.sx, tmpj = aiPos.sy - 1;tmpi < aiPos.ex;tmpi++)
			{
				if(aiJudgePad(chPad, color, tmpi, tmpj))
				{
					chPad[tmpi * 15 + tmpj] = color;
					return;
				}
			}

			for(tmpi = aiPos.sx, tmpj = aiPos.sy + 1;tmpi < aiPos.ex;tmpi++)
			{
				if(aiJudgePad(chPad, color, tmpi, tmpj))
				{
					chPad[tmpi * 15 + tmpj] = color;
					return;
				}
			}	
		}
	}
	if(aiPos.mode == 3)
	{
		if(aiJudgePad(chPad, color, aiPos.sx - 1, aiPos.sy - 1))
		{
			chPad[(aiPos.sx - 1) * 15 + aiPos.sy - 1] = color;
			return;
		}
		else if(aiJudgePad(chPad, color, aiPos.ex + 1, aiPos.ey + 1))
		{
			chPad[(aiPos.ex + 1) * 15 + aiPos.ey + 1] = color;
			return;
		}
		else
		{
			for(tmpi = aiPos.sx, tmpj = aiPos.sy - 1;tmpi < aiPos.ex;tmpi++, tmpj++)
			{
				if(aiJudgePad(chPad, color, tmpi, tmpj))
				{
					chPad[tmpi * 15 + tmpj] = color;
					return;
				}
			}

			for(tmpi = aiPos.sx, tmpj = aiPos.sy + 1;tmpi < aiPos.ex;tmpi++, tmpj++)
			{
				if(aiJudgePad(chPad, color, tmpi, tmpj))
				{
					chPad[tmpi * 15 + tmpj] = color;
					return;
				}
			}	
		}
	}
	if(aiPos.mode == 4)
	{
		if(aiJudgePad(chPad, color, aiPos.sx - 1, aiPos.sy + 1))
		{
			chPad[(aiPos.sx - 1) * 15 + aiPos.sy + 1] = color;
			return;
		}
		else if(aiJudgePad(chPad, color, aiPos.ex + 1, aiPos.ey - 1))
		{
			chPad[(aiPos.ex + 1) * 15 + aiPos.ey - 1] = color;
			return;
		}
		else
		{
			for(tmpi = aiPos.sx, tmpj = aiPos.sy - 1;tmpi < aiPos.ex;tmpi++, tmpj--)
			{
				if(aiJudgePad(chPad, color, tmpi, tmpj))
				{
					chPad[tmpi * 15 + tmpj] = color;
					return;
				}
			}

			for(tmpi = aiPos.sx, tmpj = aiPos.sy + 1;tmpi < aiPos.ex;tmpi++, tmpj--)
			{
				if(aiJudgePad(chPad, color, tmpi, tmpj))
				{
					chPad[tmpi * 15 + tmpj] = color;
					return;
				}
			}	
		}
	}

}

