/*************************************************************************
	> File Name: ./src/func.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Sat 21 Feb 2015 03:47:37 PM CST
 ************************************************************************/

#include"ls.h"

void getFileInfo(char *path)
{
	char buf[12] = "----------.";
	char *month[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	struct stat dirStat;
	memset(&dirStat, 0, sizeof(dirStat));

	if(stat(path, &dirStat) == -1)
	{
		perror("stat");
		exit(1);
	}

	modeToStr(dirStat.st_mode, buf);

	struct tm *ptime = gmtime(&dirStat.st_ctime);

	printf("%s %2u %s %s %4u %s %u %2u:%2u ", buf, dirStat.st_nlink, getpwuid(dirStat.st_uid) -> pw_name, getgrgid(dirStat.st_gid) -> gr_name, dirStat.st_size, month[ptime -> tm_mon], ptime -> tm_mday, ptime -> tm_hour, ptime -> tm_min);
}

void getDirInfo(char *path, int flag)
{
	DIR *pDIR;
	struct dirent *dirInfo;

	if((pDIR = opendir(path)) == NULL)
	{
		perror("opendir error");
		exit(1);
	}

	chdir(path);

	char pathBuf[128];
	memset(pathBuf, 0, 128);

	while((dirInfo = readdir(pDIR)) != NULL)
	{
		if(strcmp(dirInfo -> d_name, ".") == 0 || strcmp(dirInfo -> d_name, "..") == 0)
			continue;
	//	getFileInfo(dirInfo -> d_name);
		if(flag == 1)
			printf("	");
		sprintf(pathBuf, "%s/%s", getcwd(NULL, 0), dirInfo -> d_name);
		if(DT_DIR & dirInfo -> d_type)
		{
			if(flag == 1)
				printf("│");
			printf("\033[34m%s\n\033[0m", dirInfo -> d_name);
			getDirInfo(pathBuf, 1);
		}
		else
		{
			if(flag == 1)
				printf("	");
			printf("│%s\n", dirInfo -> d_name);
		}
	}

	chdir("..");

	closedir(pDIR);
}

static void modeToStr(mode_t mode, char *buf)
{
	if(S_ISREG(mode))
		buf[0] = '-';
	else if(S_ISDIR(mode))
		buf[0] = 'd';
	else if(S_ISCHR(mode))
		buf[0] = 'c';
	else if(S_ISBLK(mode))
		buf[0] = 'b';
	else if(S_ISFIFO(mode))
		buf[0] = 'p';
	else if(S_ISLNK(mode))
		buf[0] = 'l';
	else if(S_ISSOCK(mode))
		buf[0] = 's';

	if(S_IRUSR & mode)
		buf[1] = 'r';
	if(S_IWUSR & mode)
		buf[2] = 'w';
	if(S_IXUSR & mode)
		buf[3] = 'x';

	if(S_IRGRP & mode)
		buf[4] = 'r';
	if(S_IWGRP & mode)
		buf[5] = 'w';
	if(S_IXGRP & mode)
		buf[6] = 'x';

	if(S_IROTH & mode)
		buf[7] = 'r';
	if(S_IWOTH & mode)
		buf[8] = 'w';
	if(S_IXOTH & mode)
		buf[9] = 'x';
}

